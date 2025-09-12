Got it 👍 You want the **whole project** (roscore + rosserial + your Python node) to run automatically at login using **Startup Applications**, not systemd.
Let’s redo the setup from scratch, but tailored for **Startup Applications**.

---

## **Step 1 — Create a launch file**

Since a `.launch` file starts **roscore automatically**, you don’t need a separate terminal for it.
Put both rosserial and your keyboard node inside it.

1. Go to your package:

   ```bash
   cd ~/catkin_ws/src/robot_control/launch
   ```

   *(make the `launch` folder if it doesn’t exist)*

2. Create a file:

   ```bash
   nano auto_start.launch
   ```

3. Paste this:

   ```xml
   <launch>
       <!-- Connect Arduino -->
       <node pkg="rosserial_python" type="serial_node.py" name="rosserial_arduino"
             args="_port:=/dev/ttyACM0 _baud:=57600" output="screen" />

       <!-- Keyboard motor control -->
       <node pkg="robot_control" type="ros_key_control.py" name="keyboard_motor_control" output="screen" />
   </launch>
   ```

4. Save & exit.

✅ Test it:

```bash
roslaunch robot_control auto_start.launch
```

This should start everything.

---

## **Step 2 — Create a wrapper script**

Startup Applications needs a **single executable command**, so we wrap the sourcing + roslaunch in a script.

1. Make a script in your home folder:

   ```bash
   nano ~/start_robot.sh
   ```

2. Add this:

   ```bash
   #!/bin/bash
   # Load ROS environment
   source /opt/ros/noetic/setup.bash
   source /home/$USER/catkin_ws/devel/setup.bash

   # Launch your project
   roslaunch robot_control auto_start.launch
   ```

3. Save & make it executable:

   ```bash
   chmod +x ~/start_robot.sh
   ```

✅ Test it manually:

```bash
~/start_robot.sh
```

If it works, you’re ready.

---

## **Step 3 — Add to Startup Applications**

1. Press **Super** (Windows key), search **Startup Applications**, and open it.
2. Click **Add** → Fill in:

   * **Name:**

     ```
     Robot Project Autostart
     ```
   * **Command:**

     ```
     gnome-terminal -- bash -c "/home/$USER/start_robot.sh; exec bash"
     ```

     > This opens your script in a terminal so you can see logs/errors.
   * **Comment:**

     ```
     Start ROS, Arduino (rosserial), and keyboard control on login
     ```
3. Save.

---

## **Step 4 — Reboot and check**

* After logging in, a terminal should pop up automatically and run your project.
* If Arduino sometimes isn’t detected fast enough, you can add a short delay to your script:

  ```bash
  sleep 5
  ```

---

✨ Done — now every time you log in, your ROS project (roscore + rosserial + keyboard control) runs automatically.

👉 Do you want me to also make the script open **multiple terminal tabs** (one for roscore, one for rosserial, one for keyboard node) so it looks exactly like how you normally start it manually?
