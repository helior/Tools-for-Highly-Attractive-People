<?php

/**
 * @file
 * Plugin to provide an relationship handler for nodes of type TV Show, TV
 * Season or TV Episode.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('★ Entity From $_GET param'),
  'keyword' => 'entity',
  'description' => t('Creates a context for the entity with the id in the $_GET param.'),
  'context' => 'hap_entity_from_get_param',
  'edit form' => 'hap_entity_from_get_param_settings_form',
  'defaults' => array(
    'entity_bundle' => '',
    'param_name' => '',
  ),
  'context name' => 'paramcontext',
);

/**
 * Return a new context based on an existing context.
 */
function hap_entity_from_get_param($context, $conf) {
  // If unset it wants a generic, unfilled context, which is just NULL.
  if (empty($conf['entity_bundle']) || empty($conf['param_name'])) {
    return ctools_context_create_empty('node', NULL);
  }
  list($entity_type, $bundle) = explode(':', $conf['entity_bundle']);

  if (!empty($_GET[$conf['param_name']])) {
    $entity_id = $_GET[$conf['param_name']];
    if ($entities = entity_load($entity_type, array($entity_id))) {
      $entity = reset($entities);
      // If the user selected a specific bundle then return an empty context if
      // the entity is not of the provided bundle.
      if (!empty($bundle)) {
        list(,,$entity_bundle) = entity_extract_ids($entity_type, $entity);
        if ($bundle != $entity_bundle) {
          ctools_context_create_empty('entity:' . $entity_type, NULL);
        }
      }
      // Return the context.
      return ctools_context_create('entity:' . $entity_type, $entity);
    }
  }
  // If we get here it means that we could not find the context.
  return ctools_context_create_empty('entity:' . $entity_type, NULL);
}

/**
 * Settings form for the relationship.
 */
function hap_entity_from_get_param_settings_form($form, &$form_state) {
  $conf = $form_state['conf'];
  // Allow the user to select what kind of entity they want to create.
  $entities_info = entity_get_info();
  // Get a list of entity configuration.
  $options = array();
  foreach ($entities_info as $entity_type => $entity_info) {
    $options[$entity_info['label']] = array($entity_type . ':' => t('- Any bundle -'));
    // If the entity can have multiple bundles, add them as an option too.
    if (!empty($entity_info['entity keys']['bundle'])) {
      $bundle_list = $entity_info['bundles'];
      foreach ($bundle_list as $bundle_name => $bundle) {
        $options[$entity_info['label']][$entity_type . ':' . $bundle_name] = $bundle['label'];
      }
    }
  }

  $form['entity_bundle'] = array(
    '#type' => 'select',
    '#title' => t('Bundle'),
    '#description' => t('Select the bundle you want to load.'),
    '#options' => $options,
    '#default_value' => empty($conf['entity_bundle']) ? NULL : $conf['entity_bundle'],
    '#required' => TRUE,
  );

  $form['param_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Param name'),
    '#description' => t('The name of the $_GET parameter to get the entity ID from.'),
    '#default_value' => empty($conf['param_name']) ? '' : $conf['param_name'],
    '#required' => TRUE,
  );
  return $form;
}
