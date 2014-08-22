<?php

$plugin = array(
  'title' => t('★ Anchor'),
  'description' => t('Renders a named anchor (<a>) html element.'),
  'category' => t('Miscellaneous'),
  'no title override' => TRUE,
  'defaults' => array(
    'id' => '',
  ),
);

/**
 * Render callback.
 */
function hap_anchor_content_type_render($subtype, $conf, $panel_args, $context) {
  $element = new stdClass();
  $element->module = 'hap';
  $element->content = '<a id="' . $conf['id'] . '"></a>';

  return $element;

}

/**
 * Settings form callback.
 */
function hap_anchor_content_type_edit_form($form, &$form_state) {
  $form['id'] = array(
    '#type' => 'textfield',
    '#title' => t('ID attribute'),
    '#description' => t('Provide the identifier for your anchor so you can link to it with a url fragment.'),
    '#required' => TRUE,
    '#default_value' => $form_state['conf']['id'],
  );

  return $form;
}

/**
 * Submission handler for settings callback.
 */
function hap_anchor_content_type_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

/**
 * Admin title callback.
 */
function hap_anchor_content_type_admin_title($subtype, $conf, $context) {
  return t('%label named anchor', array('%label' => $conf['id']));
}
