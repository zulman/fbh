var fbh = {};
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
  var APP_ID = "265416576912150";

  /**
   * @const
   * @type {bool}
   */
  var VERBOSE = true;

  /**
   * Fb app access scope
   */
  var SCOPE = {
    scope: 'user_likes'
  };
  /**
   * Loads items from standart via google search
   * Using for phrase semantic analogs search
   * @param  {string}   query
   * @param  {Function} callback [description]
   */

  function loadGoogleItems(query, callback) {
    // var qr = q.split(' ').join('+');
    $.getJSON(GOOGLE_SEARCH_URL, {
      q: query,
    }, function(r) {
      console.log("google api response", r);
      if (callback && r && r.responseData && r.reponseData.results) {
        callback(r.reponseData.results);
      }

    });
  };

  /**
   * Auth status changed handler
   * Calss if user login or entering already registred app
   * @param  {object} response
   */

  function onAuthStatusChanged(response) {
    console.log("onAuthStatusChanged", response);
    if (response.authResponse && response.status == "connected") {
      console.log("user connected", response.authResponse.userID);
      ui.updateUserInfo();
    }
  }

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
   * [Facebook API calls]
   */

  function login() {
    console.log("Login in...");
    FB.login(function(response) {}, SCOPE);
  }

  function getUserFriends(callback) {
    loadFbData("/me/friends?limit=25", callback);
    // FB.api('/me/friends?limit=25', function(response) {
    //   console.log('friends loaded', response);
    //   if (!response.error) {
    //     var friends = response.data;
    //     if (friends && callback) callback(friends);
    // var markup = '';
    // for (var i = 0; i < friends.length; i++) {
    //   var friend = friends[i];
    //   markup += '<div ><img class="circular" src="' + getUserPicture(friend.id) + '"> ' + friend.name + '</div>';
    // }
    // document.getElementById('user-friends').innerHTML = markup;
    //   }
    // });
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
      else console.warning("error on fb data loading", response.error);
    });
  }


  /**
   * [UI]
   */
  var fbh.ui = {};
  fbh.ui.updateUserInfo = function() {
    loadFbData("/me&fields=id,name,picture", function(data) {
      console.log("callback", data);
      document.getElementById('user-info').innerHTML = '<img src="' + getUserPicture(data.id) + '" /img">' + data.name;
    });
  };

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
   * calls defined only function with setted data
   * @param  {Function} callback
   * @param  {object}   data
   */

  function fire(callback, data) {
    if (callback) callback(data);
  }
}());