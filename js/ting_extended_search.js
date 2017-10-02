/**
 * @file
 * JavaScript for extended search form.
 */

'use strict';

(function($) {
  Drupal.behaviors.clearExtendForm = {
    attach:function(context, settings) {
      $('#extend-form-clear', context).click(function() {
        $("#edit-language").val('');
        $("#edit-type").val('');
        $("#edit-source").val('');
        $("#edit-creator").val('');
        $("#edit-title").val('');
        $("#edit-subject").val('');
        $("#edit-search-block-form--2").val('');
        return false;
      });
    }
  };

  $(document).ready(function() {
    // Define variables.
    var search_input = $('.form-item-search-block-form input[name=search_block_form]', document);
    var advanced_link = $('#search-block-form a.fieldset-title', document);
    var filters_block = $('fieldset#edit-advanced');
    var display_on_search = Drupal.settings.ting_extended_search["ting_extended_search_search_result"];

    // Default states.
    advanced_link.addClass('closed');
    search_input.focus();

    // If display of advanced search is disabled in backend for search results
    // page, we are not displaying this.
    if ((display_on_search === 0) && ($(document).find('body').hasClass('page-search') !== false)) {
      filters_block.hide();
      advanced_link.hide();
      return;
    }

    if (search_input.is(':focus')) {
      search_input.addClass('unset-focus');
      advanced_link.css('display', 'block');

      // Don't display filters box on page load on search results page.
      if ($(document).find('body').hasClass('page-search')) {
        filters_block.addClass('collapsed');
      }

      // If filters block is visible, disable core :focus action and add classes
      // to "Advanced search" link.
      if (filters_block.is(':visible')) {
        search_input.addClass('unset-focus');
        advanced_link.removeClass('closed');
        advanced_link.addClass('opened');
      }

      // Handling "Advanced search" link click event.
      advanced_link.on('click', function () {
        // Toggling classes attached to "Advanced search" link.
        $(this).toggleClass('opened closed');
        if ($(this).hasClass('opened')) {
          // Unsetting core :focus event in order to keep search input expanded
          // state.
          search_input.addClass('unset-focus');
        }
        else {
          // Clear classes which are rewriting core behavior.
          search_input.removeClass('unset-focus');
          advanced_link.hide();
        }
      });

      // Handling search input state when link is already visible.
      if (advanced_link.is(':visible')) {
        search_input.addClass('unset-focus');
      }

      // Tracking search input changes on click action.
      search_input.on('click', function () {
        search_input.trigger('widthChanged');
      });

      // Binding trigger which will track search input changes.
      search_input.bind('widthChanged', function () {
        search_input.addClass('unset-focus');
        advanced_link.show();
      });
    }

    attachFoldOut();
  });

  Drupal.extendedQueryDisplay = function() {
    var queryText = $("input").filter("[name='search_block_form']").val();
    var parts = [];
    if (queryText) {
      parts.push(queryText);
    }
    var val;
    var label;
    $('#edit-advanced .form-item').each(function (i, elem) {
      var $val = $('input,select', elem).val();
      var $label = label = $('label', elem).text();
      if (($val) && ($label)) {
        parts.push(label + " = " + val);
      }
    });

    if (parts.length > 0) {
      $('#search-query-string').text(parts.join(Drupal.t(" AND ")));
    }
  };

  $(function () {
    // Extended search button location.
    $('.search .collapsible .fieldset-legend > a').insertBefore('.search .form-submit');

    if (!($('.form-item-ting-field-search').length && $('div.ding-user-header').length) && $('#ting-search-terms-fieldset').length) {
      $('#search-radios').addClass('two-radio-button');
    }
  });

  function attachFoldOut() {
    var foldout = Drupal.settings.ting_extended_search["ting_extended_search_foldout_event"];
    if (foldout) {
      $('.search .collapsible .fieldset-legend > a, .search .form-actions > a.fieldset-title').on('mouseenter', function() {
        $('.search .form-actions > a.fieldset-title').click();
        $('.search .form-actions > a.fieldset-title').removeClass('closed');
        $('.search .form-actions > a.fieldset-title').addClass('opened');
      });

      $('#edit-advanced').on('mouseleave', function() {
        $('.search .form-actions > a.fieldset-title').click();
        $('.search .form-actions > a.fieldset-title').addClass('closed');
        $('.search .form-actions > a.fieldset-title').removeClass('opened');
      })
    }
  }
})(jQuery);
