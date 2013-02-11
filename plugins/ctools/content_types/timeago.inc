<?php

// node context required
// get time field
// convert to seconds (unix timestamp)
// pass through format_interval()

$plugin = array(
  'title' => t('★ Time Ago..'),
  'description' => t('Formats a time interval with requested granularity.'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Node'),
  'defaults' => array(
    'granularity' => 2,
    'field' => 'created',
  ),
);

/**
 * Settings callback.
 */
function hap_timeago_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['granularity'] = array(
    '#type' => 'textfield',
    '#title' => t('Granularity'),
    '#description' => t('How many different units to display in the string.'),
    '#default_value' => $conf['granularity'],
    '#element_validate' => array('element_validate_integer_positive'),
    '#maxlength' => 1,
    '#size' => 1,
  );

  $form['field'] = array(
    '#type' => 'select',
    '#title' => t('Field'),
    '#description' => t('Specify the field on the node that represents the timestamp.'),
    '#options' => array(
      'created' => t('Created'),
      'changed' => t('Changed'),
    ),
    '#default_value' => $conf['field'],
  );

  return $form;
}

/**
 * Submission handler for settings callback.
 */
function hap_timeago_content_type_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

/**
 * Render callback.
 */
function hap_timeago_content_type_render($subtype, $conf, $panel_args, $context) {
  if (empty($context) || empty($context->data)) {
    return;
  }

  $node = $context->data;
  $time = $node->{$conf['field']};
  $format_interval = format_interval(REQUEST_TIME - $time, $conf['granularity']);
  $element = new stdClass();
  $element->module = 'hap';
  $element->content = '<span class="time-ago">' . t('!time ago', array('!time' => $format_interval)) . '</span>';

  return $element;
}

