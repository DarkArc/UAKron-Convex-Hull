// Copyright (C) 2015 Wyatt Childers & Emil Heineking
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "HullAlgorithm.hpp"

/** Destruct the current HullAlgorithm object.

    Destructs the current HullAlgorithm object.
    This destructor is manually defined due to
    the use of polymorphism with this class, and
    the need for a virtual destructor.
 */
HullAlgorithm::~HullAlgorithm() { }

/** Retrieve the total time spent.

    Retrieves the total time the algrorithm
    spent processing, not including the time
    spent creating HullStates.

    @returns the total time the algorithm
    spent processing in microseconds.
 */
double HullAlgorithm::getTime() const {
  return elapsedTime;
}

/** Initialize the time tracker.

    Initializes the time tracker by reseting
    the elapsed time to 0, and setting the
    last time update to the current time.
 */
void HullAlgorithm::timeTrackInit() {
  elapsedTime = 0;
  last = std::chrono::high_resolution_clock::now();
}

/** Update the time tracker.

    Updates the time tracker forcing the last
    time update to the current time.

    No time is added by this operation to the total
    time.
 */
void HullAlgorithm::timeTrackUpdate() {
  last = std::chrono::high_resolution_clock::now();
}

/** Update the time tracker, and record the difference.

    Takes the current time and subtracts the last time
    (the previously recorded time) from it. This time
    is then counted in microseconds, and added to the
    total ellapsed time. Finally, the last time
    is set to the current time.
 */
void HullAlgorithm::timeTrackRecord() {
  // Get the time difference in microseconds
  std::chrono::duration<double, std::micro> timeFragment(std::chrono::high_resolution_clock::now() - last);
  // Add the difference to the total
  elapsedTime += timeFragment.count();
  // Reset the last time variable
  last = std::chrono::high_resolution_clock::now();
}
