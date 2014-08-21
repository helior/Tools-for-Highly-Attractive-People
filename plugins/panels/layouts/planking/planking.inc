<?php

/**
 * @file
 * Layout builder for n amount of stacked regions.
 */

$plugin = array(
  'title' => t('Planking'),
  'category' => t('Highly Attractive'),
  'icon' => 'planking.png',
  'theme' => 'hap_planking_panels_layout',
  'settings form' => 'hap_planking_layout_settings_form',
  'builder' => TRUE,
  'regions function' => 'hap_planking_regions',
  'default' => array('rows' => 1, 'wrap_regions' => FALSE),
);

/**
 * Settings form callback.
 */
function hap_planking_layout_settings_form($display, $layout, $conf) {
  $form['rows'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of Rows'),
    '#default_value' => isset($conf['rows']) ? $conf['rows'] : 1,
    '#size' => '3',
  );

  $form['wrap_regions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Wrap region content with divs'),
    '#default_value' => isset($conf['wrap_regions']) ? $conf['wrap_regions'] : FALSE,
  );

  return $form;
}

/**
 * Region callback.
 */
function hap_planking_regions($display, $settings, $layout) {
  hap_include('format');
  $regions = array();

  foreach (range(1, $settings['rows']) as $row) {
    $regions[$row] = hap_format_ordinal($row);
  }

  return $regions;
}

/**
 * Implements template_preprocess_HOOK().
 */
function template_preprocess_hap_planking_panels_layout(&$vars) {
  $display = $vars['display'];
  if (isset($vars['classes_array'])) {
    $vars['attributes_array']['class'] = $vars['classes_array'];
  }

  $vars['attributes_array']['class'][] = 'planking';

  if (isset($display->css_id) && $display->css_id) {
    $vars['attributes_array']['id'] = $display->css_id;
  }
}

/**
 * Theme callback.
 */
function theme_hap_planking_panels_layout($vars) {
  $output  = '<div' . drupal_attributes($vars['attributes_array']) . '>';

  if (isset($vars['settings']['wrap_regions']) && $vars['settings']['wrap_regions']) {
    hap_include('format');
    foreach ($vars['content'] as $delta => $content) {
      if (!empty($content)) {
        $output .= '<div class="plank plank-' . hap_format_ordinal($delta) . '-region"><div class="plank-inner">' . $content . '</div></div>';
      }
    }
  }
  else {
    $output .= implode("\n", $vars['content']);
  }
  $output .= '</div>';
  return $output;
}
