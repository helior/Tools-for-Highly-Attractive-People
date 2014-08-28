<?php

/**
 * @file
 */

/**
 * Theme callback for Panels Passthrough.
 */
function theme_hap_panels_extras_passthrough_page($variables) {
  return drupal_render($variables['page']['content']);
}
