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

	public Text pictionaryRedScore;
	public Text pictionaryBlueScore;
	public Text pictionaryYellowScore;
	public Text pictionaryGreenScore;

	public Text reflexRedScore;
	public Text reflexBlueScore;
	public Text reflexYellowScore;
	public Text reflexGreenScore;

	public BatteryStatusUIController batteryStatusController;




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

	public void translateBatteryLevel(string jsonString){
		BatteryInfo info = JsonUtility.FromJson<BatteryInfo> (jsonString);
		batteryStatusController.setBatteryLevel (info.battery);
	}

	public void translatePictionaryInfo (string jsonString){
		PictionaryInfo info = JsonUtility.FromJson<PictionaryInfo> (jsonString);
		if (info == null) {
			return;
		}

		if (info.now_showing == "red") {
			playerColorBackground.color = Color.red;
		} else if (info.now_showing == "blue") {
			playerColorBackground.color = Color.blue;
		} else if (info.now_showing == "green") {
			playerColorBackground.color = Color.green;
		} else if (info.now_showing == "yellow") {
			playerColorBackground.color = Color.yellow;
		}

		if (info.now_answering == "red") {
			showPictionaryDialog (Player.RED);
		} else if (info.now_answering == "blue") {
			showPictionaryDialog (Player.BLUE);
		} else if (info.now_answering == "green") {
			showPictionaryDialog (Player.GREEN);
		} else if (info.now_answering == "yellow") {
			showPictionaryDialog (Player.YELLLOW);
		}

		pictionaryRedScore.text = info.red;
		pictionaryBlueScore.text = info.blue;
		pictionaryYellowScore.text = info.yellow;
		pictionaryGreenScore.text = info.green;

		batteryStatusController.setBatteryLevel (info.battery);

	}

	public void translateReflexInfo (string jsonString){
		ReflexInfo info = JsonUtility.FromJson<ReflexInfo> (jsonString);
		if (info == null) {
			return;
		}

		reflexRedScore.text = info.red;
		reflexBlueScore.text = info.blue;
		reflexYellowScore.text = info.yellow;
		reflexGreenScore.text = info.green;

		batteryStatusController.setBatteryLevel (info.battery);

	}


	public void showPictionaryDialog(Player player){
		if (Application.platform == RuntimePlatform.Android) {
			MobileNativePopups.OpenAlertDialog (
				"Player " + player + " answers!", "Accept or decline his answer.",
				"Accept", "Decline",
				() => {
					Debug.Log ("Accept was pressed");
				}, () => {
				Debug.Log ("Cancel was pressed");
			});
		}
		//Server answers
	}

	public void toastServerError( long errorCode ){
		if (Application.platform == RuntimePlatform.Android) {
			AndroidNativePopups.OpenToast ("Connection error, code: " + errorCode, AndroidNativePopups.ToastDuration.Long);
		}
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
