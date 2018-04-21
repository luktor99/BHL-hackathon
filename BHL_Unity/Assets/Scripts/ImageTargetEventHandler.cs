using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Vuforia;

// This is based on the DefaultTrackableEventHandler by Vuforia.
// It enables and disables the assigned canvas.
public class ImageTargetEventHandler : MonoBehaviour,
ITrackableEventHandler
{
	// Objects activated when marker is visible
	#region PUBLIC_MEMBER_VARIABLES
	public List<GameObject> ObjectsToActivate;
	public List<GameObject> ObjectsToDeactivate;
	#endregion

	#region PRIVATE_MEMBER_VARIABLES

	private TrackableBehaviour mTrackableBehaviour;

	#endregion // PRIVATE_MEMBER_VARIABLES



	#region UNTIY_MONOBEHAVIOUR_METHODS

	void Start()
	{
		mTrackableBehaviour = GetComponent<TrackableBehaviour>();
		if (mTrackableBehaviour)
		{
			mTrackableBehaviour.RegisterTrackableEventHandler(this);
		}

		// Make sure all is deactivated
		if (ObjectsToActivate != null) {
			foreach (GameObject gameObject in ObjectsToActivate)
				gameObject.SetActive (false);
		}
		if (ObjectsToDeactivate != null) {
			foreach (GameObject gameObject in ObjectsToDeactivate)
				gameObject.SetActive (false);
			}
	}

	#endregion // UNTIY_MONOBEHAVIOUR_METHODS



	#region PUBLIC_METHODS

	/// <summary>
	/// Implementation of the ITrackableEventHandler function called when the
	/// tracking state changes.
	/// </summary>
	public void OnTrackableStateChanged(
		TrackableBehaviour.Status previousStatus,
		TrackableBehaviour.Status newStatus)
	{
		if (newStatus == TrackableBehaviour.Status.DETECTED ||
			newStatus == TrackableBehaviour.Status.TRACKED ||
			newStatus == TrackableBehaviour.Status.EXTENDED_TRACKED)
		{
			OnTrackingFound();
		}
		else
		{
			OnTrackingLost();
		}
	}

	#endregion // PUBLIC_METHODS



	#region PRIVATE_METHODS


	private void OnTrackingFound()
	{
		Renderer[] rendererComponents = GetComponentsInChildren<Renderer>(true);
		Collider[] colliderComponents = GetComponentsInChildren<Collider>(true);

		// Enable objects that are supposed to show up after recognising a marker
		if (ObjectsToActivate != null) {
			foreach (GameObject gameObject in ObjectsToActivate)
				gameObject.SetActive (true);
		}
		// Disable everything else
		if (ObjectsToDeactivate != null) {
			foreach (GameObject gameObject in ObjectsToDeactivate)
				gameObject.SetActive (false);
		}

		// Enable rendering:
		foreach (Renderer component in rendererComponents)
		{
			component.enabled = true;
		}

		// Enable colliders:
		foreach (Collider component in colliderComponents)
		{
			component.enabled = true;
		}

		Debug.Log("Trackable " + mTrackableBehaviour.TrackableName + " found");
	}


	private void OnTrackingLost(){
		Renderer[] rendererComponents = GetComponentsInChildren<Renderer>(true);
		Collider[] colliderComponents = GetComponentsInChildren<Collider>(true);

		foreach (GameObject gameObject in ObjectsToActivate)
			gameObject.SetActive (false);
		//		//Disable all objects after tracking is lost
		//		if (ObjectsToActivate != null) {
		//			ObjectsToActivate.SetActive (false);
		//		}
		// Disable rendering:
		foreach (Renderer component in rendererComponents)
		{
			component.enabled = false;
		}

		// Disable colliders:
		foreach (Collider component in colliderComponents)
		{
			component.enabled = false;
		}

		Debug.Log("Trackable " + mTrackableBehaviour.TrackableName + " lost");
	}



	#endregion // PRIVATE_METHODS}

}
