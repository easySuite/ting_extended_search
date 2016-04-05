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
  $strongarm->name = 'ting_ext_search_fields_settings';
  $strongarm->value = array(
    0 => array(
      'title' => 'Title',
      'machine_name' => 'title',
      'placeholder' => 'Enter title',
      'index' => 'dkcclterm.ti',
      'type' => 'textfield',
      'values' => array(
        'type' => 'ting_well_types',
        'list' => '',
      ),
      'column' => 'left',
      'sort' => 'alphabetic_asc',
      'status' => 1,
      'weight' => '-10',
    ),
    1 => array(
      'title' => 'Author',
      'machine_name' => 'author',
      'placeholder' => 'Enter author',
      'index' => 'term.creator',
      'type' => 'textfield',
      'values' => array(
        'type' => 'ting_well_types',
        'list' => '',
      ),
      'column' => 'left',
      'sort' => 'alphabetic_asc',
      'status' => 1,
      'weight' => '-9',
    ),
    2 => array(
      'title' => 'Subject',
      'machine_name' => 'subject',
      'placeholder' => 'Enter subject keywords',
      'index' => 'term.subject',
      'type' => 'textfield',
      'values' => array(
        'type' => 'ting_well_types',
        'list' => '',
      ),
      'column' => 'left',
      'sort' => 'alphabetic_asc',
      'status' => 1,
      'weight' => '-8',
    ),
    3 => array(
      'title' => 'DK5',
      'machine_name' => 'dk5',
      'placeholder' => 'Enter DK5 number',
      'index' => 'facet.dk5',
      'type' => 'textfield',
      'values' => array(
        'type' => 'ting_well_types',
        'list' => '',
      ),
      'column' => 'left',
      'sort' => 'alphabetic_asc',
      'status' => 1,
      'weight' => '-7',
    ),
    4 => array(
      'title' => 'Year',
      'machine_name' => 'year',
      'placeholder' => 'Enter year of publish',
      'index' => 'facet.date',
      'type' => 'textfield',
      'values' => array(
        'type' => 'ting_well_types',
        'list' => '',
      ),
      'column' => 'left',
      'sort' => 'alphabetic_asc',
      'status' => 1,
      'weight' => '-6',
    ),
    5 => array(
      'title' => 'Language',
      'machine_name' => 'language',
      'placeholder' => 'Language',
      'index' => 'term.language',
      'type' => 'select',
      'values' => array(
        'type' => 'custom_list',
        'list' => array(
          'arabisk' => "arabisk",
          'dansk' => "dansk",
          'engelsk' => "engelsk",
          'fransk' => "fransk",
          'italiensk' => "italiensk",
          'kalaallisut' => "kalaallisut",
          'kinesisk' => "kinesisk",
          'kroatisk' => "kroatisk",
          'kurdisk' => "kurdisk",
          'latin' => "latin",
          'norsk' => "norsk",
          'persisk' => "persisk",
          'polsk' => "polsk",
          'russisk' => "russisk",
          'serbisk' => "serbisk",
          'somalisk' => "somalisk",
          'spansk' => "spansk",
          'svensk' => "svensk",
          'tamilsk' => "tamilsk",
          'tyrkisk' => "tyrkisk",
          'tysk' => "tysk",
          'urdu' => "urdu",
          'vietnamesisk' => "vietnamesisk",
        ),
      ),
      'column' => 'right',
      'sort' => 'alphabetic_asc',
      'status' => 1,
      'weight' => '-5',
    ),
    6 => array(
      'title' => 'Material type',
      'machine_name' => 'material_type',
      'placeholder' => 'Material type',
      'index' => 'term.type',
      'type' => 'select',
      'values' => array(
        'type' => 'ting_well_types',
        'list' => '',
      ),
      'column' => 'right',
      'sort' => 'alphabetic_asc',
      'status' => 1,
      'weight' => '-4',
    ),
    7 => array(
      'title' => 'Source',
      'machine_name' => 'source',
      'placeholder' => 'Choose source',
      'index' => 'facet.acSource',
      'type' => 'select',
      'values' => array(
        'type' => 'ting_well_sources',
        'list' => '',
      ),
      'column' => 'right',
      'sort' => 'alphabetic_asc',
      'status' => 1,
      'weight' => '-3',
    ),
    8 => array(
      'title' => 'Branch',
      'machine_name' => 'branch',
      'placeholder' => 'Choose language branch',
      'index' => 'facet.branch',
      'type' => 'select',
      'values' => array(
        'type' => 'pickup_branches',
        'list' => '',
      ),
      'column' => 'right',
      'sort' => 'alphabetic_asc',
      'status' => 1,
      'weight' => '-2',
    ),
    9 => array(
      'title' => 'Target audience',
      'machine_name' => 'choose_target_audience',
      'placeholder' => 'Choose target audience',
      'index' => 'facet.category',
      'type' => 'select',
      'values' => array(
        'type' => 'custom_list',
        'list' => array(
          'børnematerialer' => 'Children',
          'voksenmaterialer' => 'Adult',
        ),
      ),
      'column' => 'right',
      'sort' => 'alphabetic_asc',
      'status' => 1,
      'weight' => '-1',
    ),
  );
  $export['ting_ext_search_fields_settings'] = $strongarm;

  return $export;
}
