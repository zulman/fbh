/**
 * 12:25 01.10.2012
 * oleg.chumakov
 */
/**
 * namespaces
 */
var fbh = {};
fbh.ui = {};
(function() {
  /**
   * @const
   * @type {String}
   */
  var GOOGLE_SEARCH_URL = "http://ajax.googleapis.com/ajax/services/search/web?v=1.0&callback=?";

  /**
   * @const
   * @type {String}
   */
  var APP_ID = "510088449003028";

  /**
   * @const
   * @type {bool}
   */
  var VERBOSE = true;

  /**
   * Fb app access scope
   */
  var SCOPE = {
    scope: 'publish_actions'
  };


  /**
   * facebook API ready callback
   */
  window.fbAsyncInit = function() {
    console.log("fbAsyncInit");
    FB.init({
      appId: APP_ID,
      status: true,
      cookie: true,
      xfbml: true,
      oauth: true
    })
    FB.Event.subscribe('auth.statusChange', onAuthStatusChanged);
  };

  /**
   * app entry point
   */
  window.onload = function() {
    if (!VERBOSE) {
      console = {};
      console.log = function() {};
    }

    var fbroot = document.getElementById('fb-root');
    if (!fbroot) {
      fbroot = document.createElement('div');
      fbroot.id = "fb-root";
      document.body.appendChild(fbroot);
    }

    var e = document.createElement('script');
    e.async = true;
    e.src = document.location.protocol + '//connect.facebook.net/en_US/all.js';
    fbroot.appendChild(e);
  }

  /**
   * Loads items from standart via google search
   * Using for phrase semantic analogs search
   * @param  {string}   query
   * @param  {Function} callback [description]
   */

  // function loadGoogleItems(query, callback) {
  //   // var qr = q.split(' ').join('+');
  //   $.getJSON(GOOGLE_SEARCH_URL, {
  //     q: query,
  //   }, function(r) {
  //     console.log("google api response", r);
  //     if (callback && r && r.responseData && r.reponseData.results) {
  //       callback(r.reponseData.results);
  //     }
  //   });
  // };
  /**
   * Auth status changed handler
   * Calss if user login or entering already registred app
   * @param  {object} response
   */

  function onAuthStatusChanged(response) {
    console.log("onAuthStatusChanged", response);
    if (response.authResponse) if (response.status == "connected") {
      console.log("user connected", response.authResponse.userID);
      initUnity();
    } else {
      console.log("user not connected yet");
      var loginB = document.createElement('a');
      fbroot.href = "javascript:fbh.login()";
      document.body.appendChild(loginB);
      console.log("login link created");
    }
  }

  /**
   * [Facebook API calls]
   */
  fbh.login = function() {
    console.log("Login in...");
    FB.login(function(response) {}, SCOPE);
  }

  /**
   * Facebook Graph API call. Callback will be fired only for success request
   * Query syntax reference - https://developers.facebook.com/docs/reference/api/
   * @param  {String}   query
   * @param  {Function} callback
   */

  function loadFbData(query, callback) {
    console.log("loading fb data...", query);
    FB.api(query, function(response) {
      console.log('fb data loaded', response);
      if (!response.error) fire(callback, response.data ? response.data : response);
      else console.warn("error on fb data loading", response.error);
    });
  }
  /**
   * [Unity]
   */
  /**
   * Sending to top scores to Unity Object
   */
  // fbh.sendLeaderBoardToUnity = function() {
  //   loadFbData('/' + APP_ID + '/scores', function(data) {
  //     for (var i = 0; i < data.length; i++) {
  //       console.log(data[i].score);
  //       console.log(data[i].user.id);
  //       console.log(data[i].user.name);
  //     }
  //   });
  // }
  /**
   * Sending user friends(ids separated with ';') to Unity Object
   */
  fbh.sendUserFriendsToUnity = function() {
    loadFbData("/me/friends?limit=25", function(data) {
      var result = "";
      for (var i = 0; i < data.length; i++) {
        result += data[i].id + ";";
      }

      var unity = getUnity();
      unity.SendMessage("#facebook", "OnFriendsReceived", result);
    });
  }

  /**
   * Saving achievemtnt via Facebook Achievements API
   * @param  {string} url of registred achievement
   */
  fbh.saveAchievement = function(achievement) {
    var params = {
      achievement: achievement
    };
    console.log("saving achievement...", achievement);
    FB.api('/me/achievements', 'post', params, function(response) {
      if (!response || response.error) {
        console.log('Error saving achievement!', response ? response.error : "empty response");
      } else {
        console.log('achievement saved');
      }
    });
  }

  /**
   * Saving score to via Facebook Scores API
   * @param  {number} score
   */
  fbh.saveScore = function(score) {
    console.log("saving score...", score);
    var params = {
      score: score
    };

    FB.api('/me/scores', 'post', params, function(response) {
      console.log(response);
      if (!response || response.error) {
        console.error('error saving score', response ? response.error : "empty response");
      } else {
        console.log("score saved", score);
      }
    });
  }

  /**
   * Unity base object accessor
   */

  function getUnity() {
    if (typeof unityObject != "undefined") {
      return unityObject.getObjectById("unityPlayer");
    }
    return null;
  }
  /**
   * Inits unity game container
   */

  function initUnity() {
    console.log("initing unity player...");
    if (typeof unityObject != "undefined") {
      unityObject.embedUnity("unityPlayer", "assets/game.unity3d", 750, 450);
    }
  }
  /**
   * [Tools]
   */

  /**
   * Gets picture url by facebook uid
   * @param  {string} id
   */

  function getUserPicture(id) {
    return "https://graph.facebook.com/" + id + "/picture?type=normal";
  }
  /**
   * Calls defined only function with setted data
   * @param  {Function} callback
   * @param  {object}   data
   */

  function fire(callback, data) {
    if (callback) callback(data);
  }
}());