<?php

/**
 * @file
 *  Adds all kinds of fun stuff to Panels.
 */


/**
 * Implements hook_hap_info().
 */
function hap_panels_extras_hap_info() {
  return array(
    'name' => 'Panels Extras',
    'description' => 'Provides all sorts of fun stuff to the Panels General Settings.',
    'hooks' => array('ctools_render_alter', 'form_panels_panel_context_edit_settings_alter', 'theme', 'page_build'),
    'dependencies' => array(
      'modules' => array('panels', 'ctools'),
    ),
  );
}

/**
 * Implements hook_theme().
 */
function hap_panels_extras_theme() {
  return array(
    'hap_panels_extras_page' => array(
      'path' => hap_path('theme'),
      'file' => 'hap_panels_extras.inc',
      'render element' => 'page',
    ),
  );
}

/**
 * Implements hook_page_build().
 */
function hap_panels_extras_page_build(&$page) {
  if (hap_panels_extras_passthrough()) {
    $page['#theme'] = 'hap_panels_extras_passthrough_page';
  }
}

/**
 * Implementation of hook_ctools_render_alter().
 */
function hap_panels_extras_ctools_render_alter($info, $page, $context) {
  $conf = $context['handler']->conf;

  if (isset($conf['hap_panels_extras']['passthrough']) && $conf['hap_panels_extras']['passthrough']) {
    hap_panels_extras_passthrough(TRUE);
  }

  if (isset($conf['hap_panels_extras']['suppress_admin_menu']) && $conf['hap_panels_extras']['suppress_admin_menu']) {
    module_invoke('admin_menu', 'suppress');
  }

  if (isset($conf['hap_panels_extras']['assets']) && !empty($conf['hap_panels_extras']['assets'])) {
    $assets = hap_panels_extras_assets();

    foreach ($conf['hap_panels_extras']['assets'] as $asset) {
      foreach (array('css', 'js', 'library') as $type) {
        if (!empty($assets[$asset][$type])) {
          $function = 'drupal_add_' . $type;
          foreach ($assets[$asset][$type] as $item) {
            call_user_func_array($function, $item);
          }
        }
      }
    }
  }
}


/**
 * Implements hook_form_FORM_ID_alter().
 * @see panels_panel_context_edit_settings().
 */
function hap_panels_extras_form_panels_panel_context_edit_settings_alter(&$form, &$form_state) {
  $conf = $form_state['handler']->conf;
  $form['#submit'][] = '_hap_panels_extras_panels_panel_context_edit_settings_submit';

  $form['hap_panels_extras'] = array(
    '#type' => 'fieldset',
    '#title' => 'Panels Extras',
    '#tree' => TRUE,
  );

  $form['hap_panels_extras']['passthrough'] = array(
    '#type' => 'checkbox',
    '#title' => 'Enable Page Passthrough',
    '#default_value' => isset($conf['hap_panels_extras']['passthrough']) ? $conf['hap_panels_extras']['passthrough'] : FALSE,
  );

  $form['hap_panels_extras']['suppress_admin_menu'] = array(
    '#type' => 'checkbox',
    '#title' => 'Suppress Admin Menu',
    '#access' => module_exists('admin_menu'),
    '#default_value' => isset($conf['hap_panels_extras']['suppress_admin_menu']) ? $conf['hap_panels_extras']['suppress_admin_menu'] : FALSE,
  );

  $assets_options = _hap_panels_extras_assets_options();
  $form['hap_panels_extras']['assets'] = array(
    '#type' => 'checkboxes',
    '#options' => $assets_options,
    '#title' => 'Highly Attractive Panels Assets',
    '#access' => !empty($assets_options),
    '#default_value' => isset($conf['hap_panels_extras']['assets']) ? $conf['hap_panels_extras']['assets'] : NULL,
    '#description' => t('In Themepacket methodology, it is important that a theme packets is responsible for styling and adding behaviors to their OWN markup, and never assume relationships with external elements. That said, Panel layout plugins should not assume theme packets embedded within them, likewise, theme packets should not assume layout (width, float, margin, etc) in respect to its Panel layout. The solution is to include "application-level" stylesheets and scripts that act as the "integration" assets.'),
  );
}

/**
 * Submission handler: yeppers.
 * @see hap_panels_extras_form_panels_panel_context_edit_settings_alter().
 */
function _hap_panels_extras_panels_panel_context_edit_settings_submit($form, &$form_state) {
  foreach ($form_state['values']['hap_panels_extras'] as $key => $value) {
    $form_state['handler']->conf['hap_panels_extras'][$key] = $value;
  }
}

/**
 * Helper function to set the whether a page (any page) will skip the page
 * template.
 * @param  [boolean] $set
 */
function hap_panels_extras_passthrough($set = NULL) {
  $passthrough = &drupal_static(__FUNCTION__, FALSE);
  if (isset($set)) {
    $passthrough = $set;
  }

  return $passthrough;
}

/**
 * Retrieve a list of Panels assets.
 */
function hap_panels_extras_assets() {
  static $assets;
  if (!isset($assets)) {
    $assets = array();
    foreach (module_implements('hap_panels_extras_assets') as $module) {
      foreach (module_invoke($module, 'hap_panels_extras_assets') as $name => $info) {
        $assets[$name] = $info + array(
          'label' => '',
          'description' => '',
          'module' => $module,
          'css' => array(),
          'js' => array(),
          'library' => array(),
        );
      }
    }

    drupal_alter('hap_panels_extras_assets', $assets);
  }

  return $assets;
}

/**
 * Helper function to produce an #options array for form builders.
 */
function _hap_panels_extras_assets_options() {
  $options = array();
  foreach (hap_panels_extras_assets() as $name => $info) {
    $options[$name] = $info['label'];
  }
  return $options;
}
