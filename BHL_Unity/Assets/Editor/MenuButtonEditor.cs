using UnityEditor;

[CustomEditor(typeof(SelectableButton))]
public class MenuButtonEditor : Editor
{
	public override void OnInspectorGUI()
	{
		SelectableButton targetMenuButton = (SelectableButton)target;

		//targetMenuButton.acceptsPointerInput = EditorGUILayout.Toggle("Accepts pointer input", targetMenuButton.acceptsPointerInput);

		// Show default inspector property editor
		base.OnInspectorGUI();
	}
}