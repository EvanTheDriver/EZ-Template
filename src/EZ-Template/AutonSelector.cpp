/*
This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "main.h"


AutonSelector::AutonSelector()
{
  AutonCount = 0;
  CurrentAutonPage = 0;
  Autons = {};
}

AutonSelector::AutonSelector(std::vector<Auton> autons)
{
  AutonCount = autons.size();
  CurrentAutonPage = 0;
  //Autons();
  for(auto i : autons) {
    //Auton temp(get<0>(i), get<1>(i));
    //Autons.push_back(temp);
    Autons.emplace_back(i);
  }
}
void AutonSelector::PrintSelectedAuto()
{
  pros::lcd::clear_line(0);
  pros::lcd::set_text(0, "Page "+std::to_string(CurrentAutonPage+1));
  pros::lcd::set_text(1, Autons[CurrentAutonPage].Name);
}
void AutonSelector::CallSelectedAuto()
{
  Autons[CurrentAutonPage].CallAuton();
}
void AutonSelector::AddAutons(std::vector<Auton> autons) {
  AutonCount += autons.size();
  CurrentAutonPage = 0;
  for(auto i : autons) {
    //Auton temp(get<0>(i), get<1>(i));
    //Autons.push_back(temp);
    Autons.emplace_back(i);
  }
}



/*
void AutonSelector::AddAutons(std::vector<Auton> autons) {
  AutonCount += autons.size();
  CurrentAutonPage = 0;
  for(auto i : autons) {
    Autons.emplace_back(autons);
  }
}
*/
