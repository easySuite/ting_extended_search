<?php
/**
 * @file
 * ting_extended_search.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ting_extended_search_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access ting extended search settings'.
  $permissions['access ting extended search settings'] = array(
    'name' => 'access ting extended search settings',
    'roles' => array(
      'administrators' => 'administrators',
      'local administrator' => 'local administrator',
    ),
    'module' => 'ting_extended_search',
  );

  return $permissions;
}
