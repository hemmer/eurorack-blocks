##############################################################################
#
#     code.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import math
import os

PATH_THIS = os.path.abspath (os.path.dirname (__file__))



class Code:
   def __init__ (self):
      pass


   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      path_template = os.path.join (PATH_THIS, 'code_template.cpp')
      path_cpp = os.path.join (path, 'plugin_vcvrack.cpp')

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      template = template.replace ('%module.name%', module.name)

      template = self.replace_config_controls_bind (template, module.entities);
      template = self.replace_cascade_process (template, module.cascade_eval_list);
      template = self.replace_controls_preprocess (template, module.entities);
      template = self.replace_controls_postprocess (template, module.entities);
      template = self.replace_controls_widget (template, module.entities);

      with open (path_cpp, 'w', encoding='utf-8') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def replace_config_controls_bind (self, template, entities):
      nbr_params = 0
      nbr_inputs = 0
      nbr_outputs = 0
      nbr_lights = 0

      controls_bind_config = ''

      for entity in entities:
         if entity.is_control:
            control = entity
            category = self.control_kind_to_vcv_category (control)

            if category == 'Param':
               control.vcv_param_index = nbr_params
               controls_bind_config += '   module.ui.board.impl_bind (module.ui.%s, %s [%d]);\n' % (control.name, 'params', nbr_params)
               if control.kind == "Button":
                  controls_bind_config += '   configButton (%d, "%s");\n\n' % (nbr_params, control.name)
               elif control.kind == "Switch":
                  labels = ', '.join(['"' + label.text + '"' for label in control.labels[::-1]])                  
                  controls_bind_config += '   configSwitch (%d, 0, %d, 0, "%s", {%s});\n\n' % (nbr_params, len(control.labels) - 1, control.name, labels)
               else:
                  controls_bind_config += '   configParam (%d, decltype (module.ui.%s)::ValueMin, decltype (module.ui.%s)::ValueMax, 0.f, "%s");\n\n' % (nbr_params, control.name, control.name, control.name)
               nbr_params += 1

            elif category == 'Input':
               control.vcv_input_index = nbr_inputs
               controls_bind_config += '   module.ui.board.impl_bind (module.ui.%s, %s [%d]);\n' % (control.name, 'inputs', nbr_inputs)
               controls_bind_config += '   configInput (%d, "%s");\n\n' % (nbr_inputs, control.name)

               nbr_inputs += 1

            elif category == 'Output':
               control.vcv_output_index = nbr_outputs
               controls_bind_config += '   module.ui.board.impl_bind (module.ui.%s, %s [%d]);\n' % (control.name, 'outputs', nbr_outputs)
               controls_bind_config += '   configOutput (%d, "%s");\n\n' % (nbr_outputs, control.name)
               nbr_outputs += 1

            elif category == 'Light':
               control.vcv_light_index = nbr_lights
               controls_bind_config += '   module.ui.board.impl_bind (module.ui.%s, %s [%d]);\n' % (control.name, 'lights', nbr_lights)
               controls_bind_config += '   configLight (%d, "%s");\n\n' % (nbr_lights, control.name)
               nbr_lights += control.nbr_pins

      template = template.replace ('%module.nbr_params%', str (nbr_params))
      template = template.replace ('%module.nbr_inputs%', str (nbr_inputs))
      template = template.replace ('%module.nbr_outputs%', str (nbr_outputs))
      template = template.replace ('%module.nbr_lights%', str (nbr_lights))

      template = template.replace ('%  module.controls.bind+config%', controls_bind_config)

      return template


   #--------------------------------------------------------------------------

   def replace_cascade_process (self, template, controls):
      lines = ''

      for control in controls:
         if control.cascade_from is not None:
            lines += '   if (!inputs [%d].isConnected ())\n' % control.vcv_input_index
            lines += '   {\n'
            lines += '      inputs [%d].setVoltage (inputs [%d].getVoltage ());\n' % (control.vcv_input_index, control.cascade_from.reference.vcv_input_index)
            lines += '   }\n'

      return template.replace ('%  cascade_process%', lines)


   #--------------------------------------------------------------------------

   def replace_controls_preprocess (self, template, entities):
      lines = ''

      for entity in entities:
         if entity.is_control:
            lines += '      module.ui.%s.impl_preprocess ();\n' % entity.name

      return template.replace ('%     controls_preprocess%', lines)


   #--------------------------------------------------------------------------

   def replace_controls_postprocess (self, template, entities):
      lines = ''

      for entity in entities:
         if entity.is_control:
            lines += '      module.ui.%s.impl_postprocess ();\n' % entity.name

      return template.replace ('%     controls_postprocess%', lines)


   #--------------------------------------------------------------------------

   def replace_controls_widget (self, template, entities):
      lines = ''
      nbr_params = 0
      nbr_inputs = 0
      nbr_outputs = 0
      nbr_lights = 0

      for entity in entities:
         if entity.is_control:
            control = entity
            category = self.control_kind_to_vcv_category (control)

            func_category = category
            if func_category == 'Light':
               func_category = 'Child'

            widget = self.get_control_widget (control)

            if control.rotation is None:
               rotation = 0
            else:
               rotation = control.rotation.degree_top_down % 360

            rotation_rad = rotation * 2.0 * math.pi / 360.0

            if category == 'Param':
               index = nbr_params
               nbr_params += 1

            elif category == 'Input':
               index = nbr_inputs
               nbr_inputs += 1

            elif category == 'Output':
               index = nbr_outputs
               nbr_outputs += 1

            elif category == 'Light':
               index = nbr_lights
               nbr_lights += control.nbr_pins

            lines += '   {\n'
            lines += '      auto control_ptr = create%sCentered <%s> (mm2px (Vec (%ff, %ff)), module_, %d);\n' % (
               category, widget, control.position.x.mm, control.position.y.mm, index
            )
            lines += '      control_ptr->rotate (float (%f));\n' % rotation_rad
            lines += '      add%s (control_ptr);\n' % func_category
            lines += '   }\n'
            lines += '\n'

      return template.replace ('%  controls_widget%', lines)


   #--------------------------------------------------------------------------

   def control_kind_to_vcv_category (self, control):
      kind_category_map = {
         'AudioIn': 'Input',
         'AudioOut': 'Output',
         'Button': 'Param',
         'CvIn': 'Input',
         'CvOut': 'Output',
         'GateIn': 'Input',
         'GateOut': 'Output',
         'Led': 'Light',
         'LedBi': 'Light',
         'LedRgb': 'Light',
         'Pot': 'Param',
         'Switch': 'Param',
         'Trim': 'Param',
      }

      return kind_category_map [control.kind]


   #--------------------------------------------------------------------------
   # Returns the last non-None Simulator field

   def get_control_widget (self, control):
      for part in control.parts:
         components_node = part.net.first_kind ('components')
         comp_nodes = components_node.filter_kind ('comp')
         for comp_node in comp_nodes:
            fields_node = comp_node.first_kind ('fields')
            if fields_node != None:
               field_nodes = fields_node.filter_kind ('field')
               for field_node in field_nodes:
                  if field_node.property ('name') == 'Simulator':
                     widget = field_node.entities [2].value

      assert widget is not None

      return widget
