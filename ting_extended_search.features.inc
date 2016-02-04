<?php
/**
 * @file
 * ting_extended_search.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ting_extended_search_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
