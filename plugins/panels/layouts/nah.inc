<?php

/**
 * @file
 * Provides a single wrapping div for attributes.
 */

$plugin = array(
  'title' => t('Nah..'),
  'category' => t('Columns: 1'),
  'icon' => 'nah.png',
  'theme' => 'hap_nah_panels_layout',
  'regions' => array(
    'content' => t('Content'),
  ),
);

/**
 * Implements template_preprocess_HOOK().
 */
function template_preprocess_hap_nah_panels_layout(&$vars) {
  $display = $vars['display'];
  $vars['attributes_array']['class'] = $vars['classes_array'];

  if (isset($display->css_id) && $display->css_id) {
    $vars['attributes_array']['id'] = $display->css_id;
  }
}
