#include "GameGUI.h"
#include"Scene.h"


void GOGuiWindow::CleanUp()
{
	//empty, to be derived
}

void GOGuiWindow::ShowGUI(Scene* current_scene)
{
	//empty, to be derived
}




void MainGuiWinodw::ShowGUI(Scene* CurrentScene)
{
	//check what happend last frame
	if (quit_clicked)
	{

		this->quit_clicked = false;
		exit(0);//Exit app, bye bye, thanks for playing!
	}

	if (help_clicked)
	{
		CurrentScene->AddGuiWindow(new HelpGuiWindow());
		this->help_clicked = false;
	}

	if (set_ambiant_light_clicked)
	{
		CurrentScene->AddGuiWindow(new LightSettingsGuiWindow());
		this->set_ambiant_light_clicked = false;
		return;
	}

	//run frame
	ImGui::Begin("Main settings");
	{
		ImGui::Text("Hello! enjoy this scene!\nPress: E/e to un/lock the mouse curser\n Q/q to exit ");
		if (ImGui::Button("quit"))
		{
			quit_clicked = true;
		}

		if (ImGui::Button("help"))
		{
			help_clicked = true;
		}

		if (ImGui::Button("adjust ambiant light"))
		{
			set_ambiant_light_clicked = true;
		}
	}
	ImGui::End();                          // Buttons return true when clicked (most widgets return true when edited/activated)

}

void MainGuiWinodw::CleanUp()
{
}



void HelpGuiWindow::ShowGUI(Scene* current_scene)
{
	//check what happend last frame
	if (quit_clicked)
	{
		current_scene->RemoveGuiWindow(this);
		this->quit_clicked = false;
		return;
	}

	//run frame
	ImGui::Begin("Help");
	{
		ImGui::Text("Controls:\n v/V to move from robot view, to third person view to free view.\n e/E to lock/unlock mouse curser\n q/Q to quit" 
		);
		if (ImGui::Button("OK!"))
		{
			quit_clicked = true;
		}

	}
	ImGui::End();

}

void HelpGuiWindow::CleanUp()
{
}

void LightSettingsGuiWindow::CleanUp()
{
}

void LightSettingsGuiWindow::ShowGUI(Scene* current_scene)
{

	//check what happend last frame
	if (quit_clicked)
	{
		current_scene->RemoveGuiWindow(this);
		this->quit_clicked = false;
		return;
	}

	//run frame
	ImGui::Begin("Light settings");
	{
		
		static float f[3] = {0,0,0};//move to value of light source
		ImGui::Text("Please set the following values for the main light source at the center of scene");
		ImGui::SliderFloat3("R|G|B",f,0.0,1.0f);


		if (ImGui::Button("OK!"))
		{
			quit_clicked = true;
		}

	}
	ImGui::End();
}
