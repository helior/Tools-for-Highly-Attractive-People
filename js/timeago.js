/* 
 * Proccess all timeago span tags.
 */

(function ($) {
    if (typeof Drupal.settings.hap_timeago == "object") {
        var current = new Date();
        for(var nodeId in Drupal.settings.hap_timeago) {
            date = new Date(Drupal.settings.hap_timeago[nodeId]*1000);
            $("span.time-ago-" + nodeId).html(timeAgo(current,date).toString());
        }
    }
})(jQuery);


function timeAgo(current, previous) {

    var msPerMinute = 60 * 1000;
    var msPerHour = msPerMinute * 60;
    var msPerDay = msPerHour * 24;
    var msPerMonth = msPerDay * 30;
    var msPerYear = msPerDay * 365;

    var elapsed = current - previous;

    if (elapsed < msPerMinute) {
         return Math.round(elapsed/1000) + ' seconds agoX';
    }

    else if (elapsed < msPerHour) {
         return Math.round(elapsed/msPerMinute) + ' minutes agoX';
    }

    else if (elapsed < msPerDay ) {
         return Math.round(elapsed/msPerHour ) + ' hours agoX';
    }

    else if (elapsed < msPerMonth) {
         return Math.round(elapsed/msPerDay) + ' days agoX';
    }

    else if (elapsed < msPerYear) {
         return Math.round(elapsed/msPerMonth) + ' months agoX';
    }

    else {
         return Math.round(elapsed/msPerYear ) + ' years agoX';
    }
}