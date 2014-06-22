<?php

/**
 * @file php.inc.
 * A collection of functions I wish PHP shipped with. I'm loosely namespacing
 * for brevity.
 */

/**
 * PHP's array_filter(), but recursive.
 *
 * @param  array $input
 *
 * @param  string $callback
 *
 * @return array
 *   The filtered array.
 */
function hap_array_filter_recursive($input, $callback = null) {
  foreach ($input as &$value) {
    if (is_array($value)) {
      $value = hap_array_filter_recursive($value, $callback);
    }
  }

  return array_filter($input, $callback);
}
