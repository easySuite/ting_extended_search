<?php

/**
 * @file
 * Settings forms.
 */

/**
 * Settings forms of fields.
 */
function ting_extended_search_settings_form($form, &$form_state)  {

  $form['ting_extended_search_search_result'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show advanced search on search'),
    '#desciption' => t('Indicates when advanced search should be displayed at search result page.'),
    '#default_value' => variable_get('ting_extended_search_search_result', false),
  );

  $form['ting_extended_search_foldout_event'] = array(
    '#type' => 'checkbox',
    '#title' => t('Fouldout advanced search on mouseover event'),
    '#desciption' => t('Indicates which event will be used for opening advanced search container.'),
    '#default_value' => variable_get('ting_extended_search_foldout_event', false),
  );

  return system_settings_form($form);
}

function _ting_extended_search_field_exists($value, $form, $form_state) {
  $count = 0;
  $fields = $form_state['values']['fields'];
  unset($fields['more']);
  foreach ($fields as $field) {
    if ($value == $field['machine_name']) {
      $count++;
    }
  }
  return ($count > 1);
}

/**
 * Settings forms of fields.
 */
function ting_extended_search_settings_fields_form($form, &$form_state) {
  $form = array(
    '#tree' => TRUE,
  );

  $form['fields'] = array(
    '#prefix' => '<div id="ting-ext-search-wrapper">',
    '#suffix' => '</div>',
    '#type' => 'fieldset',
    '#title' => t('Fields'),
    '#theme' => 'ting_ext_search_fields_table',
    '#header' => array(
      t('Title'),
      '',
      t('Placeholder'),
      t('Well index'),
      t('Type'),
      '', // Keep it for value
    ),
  );

  $fields = variable_get('ting_ext_search_fields_settings', array());
  $form_state['fields'] = $fields;
  if (!isset($form_state['fields_count'])) {
    $form_state['fields_count'] = empty($fields) ? 1 : count($fields);
  }
  $fields_count = $form_state['fields_count'];
  $field_types = array(
    'textfield' => t('Textfield'),
    'select' => t('Dropdown'),
    'checkboxes' => t('Checkboxes'),
    'radios' => t('Radios'),
  );

  $value_types = array(
    'ting_well_types' => t('Well types'),
    'ting_well_sources' => t('Well sources'),
    'pickup_branches' => t('Pickup branches'),
    'custom_list' => t('Custom list'),
  );

  for ($i = 0; $i < $fields_count; $i++) {
    $form['fields'][$i]['title'] = array(
      '#type' => 'textfield',
      '#default_value' => isset($fields[$i]['title']) ? $fields[$i]['title'] : '',
    );

    $form['fields'][$i]['machine_name'] = array(
      '#type' => 'machine_name',
      '#default_value' => isset($fields[$i]['machine_name']) ? $fields[$i]['machine_name'] : '',
      '#machine_name' => array(
        'source' => array('fields', $i, 'title'),
        'exists' => '_ting_extended_search_field_exists',
      ),
      '#disabled' => isset($fields[$i]['machine_name']),
    );

    $form['fields'][$i]['placeholder'] = array(
      '#type' => 'textfield',
      '#default_value' => isset($fields[$i]['placeholder']) ? $fields[$i]['placeholder'] : '',
    );

    $form['fields'][$i]['index'] = array(
      '#type' => 'textfield',
      '#default_value' => isset($fields[$i]['index']) ? $fields[$i]['index'] : '',
    );

    $form['fields'][$i]['type'] = array(
      '#type' => 'select',
      '#options' => $field_types,
      '#default_value' => isset($fields[$i]['type']) ? $fields[$i]['type'] : 'textfield',
    );
    $form['fields'][$i]['values']['type'] = array(
      '#type' => 'select',
      '#options' => $value_types,
      '#default_value' => isset($fields[$i]['values']['type']) ? $fields[$i]['values']['type'] : 'ting_well_types',
      '#states' => array(
        'invisible' => array(
          ':input[name="fields[' . $i . '][type]"]' => array(
            'value' => 'textfield'
          ),
        ),
      ),
    );
    $value = '';
    if (isset($fields[$i]['values']['list']) && !empty($fields[$i]['values']['list']) && is_array($fields[$i]['values']['list'])) {
      $list = $fields[$i]['values']['list'];
      array_walk($list, function(&$i, $k) {
        $i = "{$k}|{$i}";
      });
      $value = implode("\r\n", $list);
    }
    $form['fields'][$i]['values']['list'] = array(
      '#type' => 'textarea',
      '#rows' => 8,
      '#cols' => 5,
      '#default_value' => $value,
      '#states' => array(
        'visible' => array(
          ':input[name="fields[' . $i . '][values][type]"]' => array('value' => 'custom_list'),
        ),
      ),
    );
  }

  $form['fields']['more'] = array(
    '#type' => 'submit',
    '#value' => t('Add another one'),
    '#submit' => array('ting_ext_search_more_submit'),
    '#limit_validation_errors' => array(),
    '#ajax' => array(
      'callback' => 'ting_ext_search_callback',
      'wrapper' => 'ting-ext-search-wrapper',
     ),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

/**
 * Ajax handler for more button.
 */
function ting_ext_search_callback($form, $form_state) {
  return $form['fields'];
}

/**
 * Submit handler for more button.
 */
function ting_ext_search_more_submit($form, &$form_state) {
  $form_state['fields_count']++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Implements hook_validation().
 */
function ting_extended_search_settings_fields_form_validate($form, &$form_state) {
  $fields = &$form_state['values']['fields'];
  foreach ($fields as $key => &$field) {
    if (is_numeric($key)) {
      if ($field['type'] != 'textfield' && $field['values']['type'] == 'custom_list') {
        $data = $field['values']['list'];
        if (preg_match('/^[^|\r\n]+\|[^|\r\n]+$/m', $data)) {
          $lines = preg_split('/[\r\n]+/i', $data);
          $field['values']['list'] = array();
          foreach ($lines as $line) {
            $parts = explode('|', $line);
            $field['values']['list'][trim($parts[0])] = trim($parts[1]);
          }
        } else {
          form_set_error('fields][' . $key. '][values][list', t('Wrong format of list. Example of item: "name|value".'));
        }
      }
    }
  }
}

/**
 * Main submit for fields form.
 */
function ting_extended_search_settings_fields_form_submit($form, &$form_state) {
  $fields = $form_state['values']['fields'];
  unset($fields['more']);
  $display = $form_state['fields'];

  for ($i = 0; $i < count($fields); $i++) {
    if (isset($display[$i]) && ($display[$i]['machine_name'] == $fields[$i]['machine_name'])) {
      $display[$i]['title'] = $fields[$i]['title'];
      $display[$i]['placeholder'] = $fields[$i]['placeholder'];
      $display[$i]['index'] = $fields[$i]['index'];
      $display[$i]['type'] = $fields[$i]['type'];
      $display[$i]['values'] = $fields[$i]['values'];
    }
    elseif (!isset($display[$i])) {
      // Add new items.
      $display[$i]['machine_name'] = $fields[$i]['machine_name'];
      $display[$i]['title'] = $fields[$i]['title'];
      $display[$i]['placeholder'] = $fields[$i]['placeholder'];
      $display[$i]['index'] = $fields[$i]['index'];
      $display[$i]['type'] = $fields[$i]['type'];
      $display[$i]['values'] = $fields[$i]['values'];
    }
  }

  $display = array_filter($display, function($f) {
    return !empty($f['title']) && !empty($f['placeholder']) && !empty($f['index']);
  });

  $display = array_values($display);
  variable_set('ting_ext_search_fields_settings', $display);
}

/**
 * Settings forms of fields.
 */
function ting_extended_search_settings_display_form($form, &$form_state) {
  $form = array(
    '#tree' => TRUE,
  );

  $form['display'] = array(
    '#type' => 'fieldset',
    '#title' => t('Fields'),
    '#theme' => 'ting_ext_search_display_table',
    '#header' => array(
      t('Field'),
      t('Column'),
      t('Sort'),
      t('Status'),
      t('Weight'),
    ),
  );

  $fields = variable_get('ting_ext_search_fields_settings', array());
  $form_state['fields'] = $fields;

  if (!isset($form_state['fields_count'])) {
    $form_state['fields_count'] = empty($fields) ? 0 : count($fields);
  }
  $fields_count = $form_state['fields_count'];

  $columns = array(
    'left' => t('Left'),
    'right' => t('Right'),
  );

  $sort_types = array(
    'alphabetic_asc' => t('Alphabetic'),
    'alphabetic_desc' => t('Alphabetic(reverse)'),
    'numeric_asc' => t('Numeric'),
    'numeric_desc' => t('Numeric(reverse)'),
  );

  for ($i = 0; $i < $fields_count; $i++) {
    $form['display'][$i]['title'] = array(
      '#type' => 'textfield',
      '#disabled' => TRUE,
      '#default_value' => isset($fields[$i]['title']) ? $fields[$i]['title'] : '',
    );

    $form['display'][$i]['column'] = array(
      '#type' => 'radios',
      '#options' => $columns,
      '#default_value' => isset($fields[$i]['column']) ? $fields[$i]['column'] : 'left',
    );

    $form['display'][$i]['sort'] = array(
      '#type' => 'select',
      '#options' => $sort_types,
      '#default_value' => isset($fields[$i]['sort']) ? $fields[$i]['sort'] : 'alphabetic_asc',
    );

    $form['display'][$i]['status'] = array(
      '#type' => 'checkbox',
      '#default_value' => isset($fields[$i]['status']) ? $fields[$i]['status'] : 1,
    );
    $form['display'][$i]['weight'] = array(
      '#type' => 'weight',
      '#default_value' => (isset($fields[$i]['weight'])) ? $fields[$i]['weight'] : 0,
      '#attributes' => array(
        'class' => array('display-weight'),
      )
    );
    $form['display'][$i]['machine_name'] = array(
      '#type' => 'hidden',
      '#value' => $fields[$i]['machine_name'],
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

/**
 * Main submit for display form.
 */
function ting_extended_search_settings_display_form_submit($form, &$form_state) {
  $display = $form_state['values']['display'];
  $fields = $form_state['fields'];

  for ($i = 0; $i < count($display); $i++) {
    if ($display[$i]['machine_name'] == $fields[$i]['machine_name']) {
      $fields[$i]['column'] = $display[$i]['column'];
      $fields[$i]['sort'] = $display[$i]['sort'];
      $fields[$i]['status'] = $display[$i]['status'];
      $fields[$i]['weight'] = $display[$i]['weight'];
    }
  }

  uasort($fields, function($a, $b) {
    if ($a['weight'] == $b['weight'])
      return 0;
    return $a['weight'] < $b['weight'] ? -1 : 1;
  });

  $fields = array_values($fields);
  variable_set('ting_ext_search_fields_settings', $fields);
}
