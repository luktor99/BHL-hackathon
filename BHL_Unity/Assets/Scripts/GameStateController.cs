using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum Game
{
	REFLEX,
	PICTIONARY
};
	
public class GameStateController : MonoBehaviour {


	private Color playerColor = Color.red;
	private Game currentGame = Game.REFLEX;

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
