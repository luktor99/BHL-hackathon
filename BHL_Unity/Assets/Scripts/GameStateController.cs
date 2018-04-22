using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum Game
{
	REFLEX,
	PICTIONARY,
	NONE
};

public enum AppState
{
	CONFIGURATION,
	REFLEX,
	PICTIONARY
};

public enum Player
{
	RED,
	BLUE,
	YELLLOW,
	GREEN
};


public class GameStateController : MonoBehaviour {


	private Color playerColor = Color.red;
	private Game currentGame = Game.NONE;
	private AppState currentAppState = AppState.CONFIGURATION;
	private int numberOfPlayers = 1;

	public void setCurrentGame(Game newGame){
		currentGame = newGame;
	}

	public Game getCurrentGame(){
		return currentGame;
	}

	public void setPlayerColor( Color newColor){
		playerColor = newColor;
	}

	public Color getPlayerColor(){
		return playerColor;
	}

	public void setNumberOfPlayers(int number){
		numberOfPlayers = number;
	}

	public int getNumberOfPlayers(){
		return numberOfPlayers;
	}

	public void setCurrentAppState( AppState state) {
		currentAppState	= state;
	}

	public AppState getCurrentAppState(){
		return currentAppState;
	}
		

	private static GameStateController _instance;

	public static GameStateController Instance { get { return _instance; } }

	private void Awake(){
		if (_instance != null && _instance != this) {
			Destroy (this.gameObject);
		} else {
			_instance = this;
		}
	}

}
