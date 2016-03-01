<?php
/**
 * @file
 * ting_extended_search.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ting_extended_search_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ting_ext_search_display_settings';
  $strongarm->value = array(
    0 => array(
      'title' => 'Title',
      'column' => 'left',
      'sort' => 'alphabetic_asc',
      'status' => 1,
      'weight' => '-10',
    ),
    1 => array(
      'title' => 'Source',
      'column' => 'right',
      'sort' => 'alphabetic_asc',
      'status' => 1,
      'weight' => '-9',
    ),
    2 => array(
      'title' => 'Material type',
      'column' => 'right',
      'sort' => 'alphabetic_asc',
      'status' => 1,
      'weight' => '-8',
    ),
    3 => array(
      'title' => 'Author',
      'column' => 'left',
      'sort' => 'alphabetic_asc',
      'status' => 1,
      'weight' => '-7',
    ),
    4 => array(
      'title' => 'Branch',
      'column' => 'right',
      'sort' => 'alphabetic_asc',
      'status' => 1,
      'weight' => '-6',
    ),
    5 => array(
      'title' => 'Language',
      'column' => 'right',
      'sort' => 'alphabetic_asc',
      'status' => 1,
      'weight' => '-5',
    ),
  );
  $export['ting_ext_search_display_settings'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ting_ext_search_fields_settings';
  $strongarm->value = array(
    0 => array(
      'title' => 'Author',
      'placeholder' => 'Enter author',
      'index' => 'term.creator',
      'type' => 'textfield',
      'values' => array(
        'type' => 'ting_well_types',
        'list' => '',
      ),
    ),
    1 => array(
      'title' => 'Branch',
      'placeholder' => 'Choose language branch',
      'index' => 'facet.branch',
      'type' => 'select',
      'values' => array(
        'type' => 'pickup_branches',
        'list' => 'ting_well_types|vget(\'ting_well_types\')
ting_well_sources|vget(\'ting_well_sources\')
pickup_branches|provider(\'pickup_branches\')',
      ),
    ),
    2 => array(
      'title' => 'Language',
      'placeholder' => 'Language',
      'index' => 'term.language',
      'type' => 'select',
      'values' => array(
        'type' => 'custom_list',
        'list' => array(
          'arabisk' => 'Arabik',
          'dansk' => 'Dansk',
          'engelsk' => 'English',
          'fransk' => 'Francoise',
        ),
      ),
    ),
    3 => array(
      'title' => 'Material type',
      'placeholder' => 'Material type',
      'index' => 'term.type',
      'type' => 'select',
      'values' => array(
        'type' => 'ting_well_types',
        'list' => '',
      ),
    ),
    4 => array(
      'title' => 'Source',
      'placeholder' => 'Choose source',
      'index' => 'facet.acSource',
      'type' => 'select',
      'values' => array(
        'type' => 'ting_well_sources',
        'list' => 'ting_well_types|vget(\'ting_well_types\')
ting_well_sources|vget(\'ting_well_sources\')
pickup_branches|provider(\'pickup_branches\')',
      ),
    ),
    5 => array(
      'title' => 'Title',
      'placeholder' => 'Enter title',
      'index' => 'dkcclterm.ti',
      'type' => 'textfield',
      'values' => array(
        'type' => 'ting_well_types',
        'list' => '',
      ),
    ),
  );
  $export['ting_ext_search_fields_settings'] = $strongarm;

  return $export;
}
