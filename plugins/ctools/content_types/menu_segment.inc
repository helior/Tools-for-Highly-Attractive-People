<?php

/**
 * Content-type plugin to render a segment of a menu tree.
 */
$plugin = array(
  'title' => t('Menu Segment'),
  'description' => t('Render a segment of a menu tree'),
  'category' => t('Miscellaneous'),
  'defaults' => array(
    'menu' => 'main-menu',
    'link_path' => '',
    'include_self' => TRUE,
  ),
);

/**
 * Settings form callback.
 */
function hap_menu_segment_content_type_edit_form($form, &$form_state) {
  $form['menu'] = array(
    '#type' => 'select',
    '#title' => t('Menu'),
    '#options' => menu_get_menus(),
    '#default_value' => $form_state['conf']['menu'],
  );

  $form['link_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Link path'),
    '#description' => t('Type the menu link path that should be the parent of the render menu.'),
    '#default_value' => $form_state['conf']['link_path'],
  );

  $form['include_self'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include self'),
    '#description' => t('If checked, will render the menu link itself as a single item in an unordered list.'),
    '#default_value' => $form_state['conf']['include_self'],
  );

  return $form;
}

/**
 * Submission handler for settings callback.
 */
function hap_menu_segment_content_type_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

/**
 * Render callback.
 */
function hap_menu_segment_content_type_render($subtype, $conf, $panel_args, $context) {
  hap_include('menu');
  $segment = hap_menu_tree_segment($conf['menu'], $conf['link_path'], $conf['include_self']);

  $element = new stdClass();
  $element->module = 'hap';
  $element->content = $segment;

  return $element;
}
