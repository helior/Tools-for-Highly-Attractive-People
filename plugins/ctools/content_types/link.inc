<?php

$plugin = array(
  'title' => t('★ Link'),
  'description' => t('Renders a link.'),
  'category' => t('Miscellaneous'),
  'no title override' => TRUE,
  'defaults' => array(
    'content' => '',
    'href' => '',
  ),
);

/**
 * Render callback.
 */
function hap_link_content_type_render($subtype, $conf, $panel_args, $context) {
  $element = new stdClass();
  $element->module = 'hap';
  $element->content = l($conf['content'], $conf['href']);

  return $element;

}

/**
 * Settings form callback.
 */
function hap_link_content_type_edit_form($form, &$form_state) {
  $form['content'] = array(
    '#type' => 'textfield',
    '#title' => t('Content'),
    '#required' => TRUE,
    '#default_value' => $form_state['conf']['content'],
  );

  $form['href'] = array(
    '#type' => 'textfield',
    '#title' => t('HREF'),
    '#required' => TRUE,
    '#default_value' => $form_state['conf']['href'],
  );

  return $form;
}

/**
 * Submission handler for settings callback.
 */
function hap_link_content_type_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

/**
 * Admin title callback.
 */
function hap_link_content_type_admin_title($subtype, $conf, $context) {
  return t('%label link', array('%label' => $conf['content']));
}
