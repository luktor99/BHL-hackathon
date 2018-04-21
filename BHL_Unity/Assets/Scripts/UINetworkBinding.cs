using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TheNextFlow.UnityPlugins;





public class UINetworkBinding : MonoBehaviour {


	const string START_PICTIONARY_TRIGGER = "StartPictionary";
	const string START_REFLEX_TRIGGER = "StartReflex";
	const string END_GAME_TRIGGER = "EndGame";

	public Image playerColorBackground;

	public SelectableButton onePlayerButton;
	public SelectableButton twoPlayersButton;
	public SelectableButton threePlayersButton;
	public SelectableButton fourPlayersButton;
	public Button connectionAndRegistrationButton;
	public Button playButton;
	public Button resetButton;

	public SelectableButton pictionaryGameButton;
	public SelectableButton reflexGameButton;

	private SelectableButton activePlayerNumberButton;
	private SelectableButton activeGameButton;

	public Animator uiAnimator;

	// Use this for initialization
	void Start () {
        onePlayerButton.onClick.AddListener(delegate { SetNumberOfPlayers(1, onePlayerButton); });
		twoPlayersButton.onClick.AddListener(delegate { SetNumberOfPlayers(2, twoPlayersButton); });
		threePlayersButton.onClick.AddListener(delegate { SetNumberOfPlayers(3, threePlayersButton); });
		fourPlayersButton.onClick.AddListener(delegate { SetNumberOfPlayers(4, fourPlayersButton); });
		connectionAndRegistrationButton.onClick.AddListener (delegate { CheckConnectionAndRegisterPlayer (); });
		pictionaryGameButton.onClick.AddListener (delegate { SetActiveGame (Game.PICTIONARY, pictionaryGameButton); });
		reflexGameButton.onClick.AddListener(delegate { SetActiveGame (Game.REFLEX, reflexGameButton); });
		playButton.onClick.AddListener (delegate { play (); });
		resetButton.onClick.AddListener (delegate { reset (); });
    }
		
    void CheckConnectionAndRegisterPlayer()
    {
		NetworkController.Instance.DoConnectAndRegisterPlayer ();
    }

	public void ConnectionSuccess(Color newColor){
		GameStateController.Instance.setPlayerColor (newColor);
		playerColorBackground.color = newColor;
	}

	void SetNumberOfPlayers(int numberOfPlayers, SelectableButton button)
    {
        Debug.Log("SetNumberOfPlayers: " + numberOfPlayers);
		GameStateController.Instance.setNumberOfPlayers (numberOfPlayers);
		if (activePlayerNumberButton != null) {
			activePlayerNumberButton.buttonSelected (false);
		}
		activePlayerNumberButton = button;
		activePlayerNumberButton.buttonSelected (true);
    }

	void SetActiveGame(Game game, SelectableButton button){
		Debug.Log ("Selected game: " + game);
		GameStateController.Instance.setCurrentGame (game);
		if (activeGameButton != null) {
			activeGameButton.buttonSelected (false);
		}
		activeGameButton = button;
		activeGameButton.buttonSelected (true);
	}

	void play(){
		NetworkController.Instance.DoPlayConfiguration ();
		// TODO WAIT FOR SERVER RESPONSE
	}

	void reset(){
		// TODO SEND RESET TO SERVER AND WAIT FOR RESPONSE
		resetSuccess();
	}
    
	public void resetSuccess(){
		uiAnimator.SetTrigger (END_GAME_TRIGGER);
	}

	public void playSuccess(){
		if (GameStateController.Instance.getCurrentGame () == Game.PICTIONARY) {
			uiAnimator.SetTrigger (START_PICTIONARY_TRIGGER);
		} else if (GameStateController.Instance.getCurrentGame () == Game.REFLEX) {
			uiAnimator.SetTrigger (START_REFLEX_TRIGGER);
		}
	}

	public void toastServerError( long errorCode ){
		AndroidNativePopups.OpenToast("Connection error, code: " + errorCode, AndroidNativePopups.ToastDuration.Long);
	}


	private static UINetworkBinding _instance;

	public static UINetworkBinding Instance { get { return _instance; } }

	private void Awake(){
		if (_instance != null && _instance != this) {
			Destroy (this.gameObject);
		} else {
			_instance = this;
		}
	}

}
