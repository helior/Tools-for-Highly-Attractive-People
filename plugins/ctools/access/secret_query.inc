<?php

/**
 * @file
 * Access plugin to check against a specific key/value query parameter.
 */

$plugin = array(
  'title' => t("★ Secret Query String"),
  'description' => t('Control access by checking for a specific key/value query parameter in request URL.'),
  'callback' => 'hap_secret_query_access_check',
  'settings form' => 'hap_secret_query_settings',
  'summary' => 'hap_secret_query_access_summary',
  'default' => array('name' => 'secret', 'value' => NULL),
);

/**
 * Access callback.
 */
function hap_secret_query_access_check($conf, $context) {
  // Refuse access if name or value is not set.
  if (!isset($conf['name']) || !isset($conf['value'])) {
    return FALSE;
  }

  // Return TRUE when parameter is set and it's value matches what is configured.
  return (isset($_GET[$conf['name']]) && $_GET[$conf['name']] == $conf['value']);
}

/**
 * Settings callback.
 */
function hap_secret_query_settings($form, &$form_state, $conf) {
  $form['settings']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Secret Parameter Name'),
    '#description' => t('Set the name of the query parameter.'),
    '#default_value' => $conf['name'],
    '#required' => TRUE,
  );

  $form['settings']['value'] = array(
    '#type' => 'textfield',
    '#title' => t('Secret Parameter Value'),
    '#description' => t('The secret value to test against for access control.'),
    '#default_value' => $conf['value'],
    '#required' => TRUE,
  );

  return $form;
}

/**
 * Summary callback.
 */
function hap_secret_query_access_summary($conf, $context) {
  return t('%query in the request parameter will grant access.', array('%query' => '?' . $conf['name'] . '=' . $conf['value']));
}
