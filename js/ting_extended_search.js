/**
 * @file
 * JavaScript for extended search form.
 */

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
      attachFoldOut();
    }
  };

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
    $('#edit-advanced a.fieldset-title').addClass( "extend-search" );
    $('.search #edit-advanced .fieldset-legend > a.extend-search').insertBefore('.site-header .search .form-submit');

    attachFoldOut();

    var openedLink = null; 
    $('input.auto-submit').mousedown(function() {
      $('input.auto-submit').addClass('extended');
      $('a.extend-search').css('visibility', 'visible');
    });

    $('.form-actions a.extend-search').click(function(event) {
      if($(event.target).hasClass('opened')) {
        openedLink = null;
        $('.form-actions a.extend-search').removeClass('opened');
        return;
      }
      $('.form-actions a.extend-search').removeClass('opened');
      openedLink = $(event.target);
      openedLink.addClass('opened');
    });

    $(document).click(function(e) {
      var $target = $(e.target);
      e.preventDefault();
      if(!openedLink && !$target.hasClass('auto-submit') && !$('a.fieldset-title.opened').length) {
        $('a.extend-search').css('visibility', 'hidden');
        $('input.auto-submit').removeClass('extended');
        return;
      }
    });

     if ($('a.search-term').length) {
        $('a.extend-search').attr('id','search-extend-term');
      }
  });

  function attachFoldOut() {
    var foldout = Drupal.settings.ting_extended_search["ting_extended_search_foldout_event"];
    if (foldout) {
      $('.search .collapsible .fieldset-legend > a, .search .form-actions > a.extend-search').on('mouseenter', function() {
        $('.search .form-actions > a.extend-search').click();
      })

      $('#edit-advanced').on('mouseleave', function() {
        $('.search .form-actions > a.extend-search').click();
      })
    }
  }

})(jQuery);
