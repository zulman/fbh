using UnityEngine;
using System.Collections;
using System;

/// <summary>
/// Class for listening js facebook api events
/// </summary>
public class Facebook : MonoBehaviour
{
  
  public GameObject BonusAch;
  public GameObject NewAch;
  public GameObject Finish;
  public Action<string[]> OnFriendsLoaded;
  public void LoadFriends()
  {
    Application.ExternalCall( "fbh.sendUserFriendsToUnity" );
  }
  public void BonusesAchievement()
  {
    Application.ExternalCall( "fbh.saveAchievement", "http://the21.ru/fbh/ach/bonus.html" );
    GameObject bon = GameObject.Instantiate( BonusAch ) as GameObject;
    Destroy( bon, 2f );
  }
  public void SaveScore( string score )
  {
    Application.ExternalCall( "fbh.saveScore", score );
    GameObject fin = GameObject.Instantiate( Finish ) as GameObject;
    fin.guiText.text = "Score: " + score;
  }
  public void NewAchievement()
  {
    Application.ExternalCall( "fbh.saveAchievement", "http://the21.ru/fbh/ach/new.html" );
    GameObject bon = GameObject.Instantiate( NewAch ) as GameObject;
    Destroy( bon, 2f );
  }
  public void OnFriendsReceived( string argument )
  {
    string[] args = argument.Split( ';' );
    Debug.Log( "OnFriendsReceived" );
    string[] result = new string[args.Length];
    for( int  i = 0; i < args.Length; i ++ ) {
      result[i] = GetUserPictureURL( args[i] );
    }
    if( OnFriendsLoaded != null )
      OnFriendsLoaded( result );
  }
  
  #region Helpers
  public string GetUserPictureURL( string id )
  {
    return string.Format( "https://graph.facebook.com/{0}/picture?type=normal", id );
  }
  #endregion
}