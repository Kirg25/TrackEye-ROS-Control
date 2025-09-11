# Startup-Application

to start our program on start up automatically



Gotcha — your current startup sequence needs three separate commands in separate terminals:

1. **roscore**
2. **rosserial** to connect Arduino
3. **keyboard control node**

We can make them all run automatically at boot on Ubuntu 20.04 by creating **one ROS launch file** and then telling `systemd` to start it after boot.

---

## **Step 1 — Create a unified ROS launch file**

Since `roscore` is already started automatically when you run a `.launch` file, you don’t need to start it separately.
We’ll make `keyboard_motor_control` and `rosserial` start together.

1. Go to your ROS package folder, for example:

   ```bash
   cd ~/catkin_ws/src/robot_control/launch
   ```

   *(If you don’t have a `launch` folder, create it.)*

2. Create a new file:

   ```bash
   nano auto_start.launch
   ```

3. Add this:

   ```xml
   <launch>
       <!-- Start rosserial to connect Arduino -->
       <node pkg="rosserial_python" type="serial_node.py" name="rosserial_arduino"
             args="_port:=/dev/ttyACM0 _baud:=57600" output="screen" />

       <!-- Start your keyboard control node -->
       <node pkg="robot_control" type="ros_key_control.py" name="keyboard_motor_control" output="screen" />
   </launch>
   ```

4. Save and exit.

---

## **Step 2 — Test the launch file**

```bash
roslaunch robot_control auto_start.launch
```

If it starts both `rosserial` and your keyboard control node without issues, you’re ready for auto-start.

---

## **Step 3 — Create a startup script**

1. Create:

   ```bash
   nano ~/start_robot.sh
   ```

2. Add:

   ```bash
   #!/bin/bash
   source /opt/ros/noetic/setup.bash
   source ~/catkin_ws/devel/setup.bash
   roslaunch robot_control auto_start.launch
   ```

3. Make it executable:

   ```bash
   chmod +x ~/start_robot.sh
   ```

---

## **Step 4 — Create a systemd service**

1. Create:

   ```bash
   sudo nano /etc/systemd/system/robot_autostart.service
   ```

2. Add:

   ```ini
   [Unit]
   Description=Robot Arduino + ROS Autostart
   After=network.target

   [Service]
   Type=simple
   User=wafiuddin   # change to your Ubuntu username
   WorkingDirectory=/home/wafiuddin
   ExecStart=/home/wafiuddin/start_robot.sh
   Restart=on-failure

   [Install]
   WantedBy=multi-user.target
   ```

3. Save and exit.

---

## **Step 5 — Enable & start**

```bash
sudo systemctl daemon-reload
sudo systemctl enable robot_autostart.service
sudo systemctl start robot_autostart.service
```

---

## **Step 6 — Check logs if something fails**

```bash
journalctl -u robot_autostart.service -b
```

---

💡 **Extra tip for Arduino USB**

* Sometimes `/dev/ttyACM0` changes after a reboot.
  You can make it permanent by creating a udev rule so it always appears as `/dev/arduino`:

  ```bash
  sudo nano /etc/udev/rules.d/99-arduino.rules
  ```

  Add:

  ```
  SUBSYSTEM=="tty", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="0043", SYMLINK+="arduino"
  ```

  *(Vendor/Product IDs depend on your Arduino model — find them with `lsusb`.)*
  Then in your launch file, replace `/dev/ttyACM0` with `/dev/arduino`.

---

If you want, I can make you **a single launch file that starts roscore, rosserial, and keyboard control** and also **waits until Arduino is connected** so it won’t crash during boot. That makes it fully hands-off — you just turn on your PC and it’s ready.

Do you want me to make that version?
You *can* put just

```bash
roslaunch robot_control auto_start.launch
```

in the **Startup Applications** command field —
but it won’t work unless you also load your **ROS environment variables** first.

---

When you run `roslaunch` in a normal terminal, you already did something like:

```bash
source /opt/ros/noetic/setup.bash
source ~/catkin_ws/devel/setup.bash
```

These commands set up things like `ROS_PACKAGE_PATH` and `PYTHONPATH` so `roslaunch` knows where to find your packages.

**Startup Applications** doesn’t automatically run your `.bashrc`, so without `source ...` first, `roslaunch` will fail with errors like:

```
roslaunch: command not found
or
[roslaunch] No package named 'robot_control'
```

---

**That’s why** the working Startup Applications command is usually:

```bash
bash -c "source /opt/ros/noetic/setup.bash && source /home/$USER/catkin_ws/devel/setup.bash && roslaunch robot_control auto_start.launch"
```

`bash -c` runs a shell, sources the setup files, and then runs `roslaunch` with your environment ready.

---

If you want, I can show you **a shortcut** so you *can* just write `roslaunch robot_control auto_start.launch` and have it still work at startup without typing the sources every time. That involves adding the sources to a small wrapper script.

Do you want me to make that wrapper?
