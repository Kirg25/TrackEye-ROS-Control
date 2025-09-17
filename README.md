

# 🛠️ TrackEye-ROS-Control

A **Final Year Project (2025)** by a Mechatronics student, integrating **Arduino** and **ROS (Robot Operating System)** for robotic control via keyboard input.

---

## 📁 Project Structure

* **Arduino Code**: `Project_MEC3_25_5`
* **ROS Package**: `robot_control`

---

## 🚀 Getting Started

### 1. **Start ROS Core**

```bash
roscore
```

### 2. **Connect to Arduino via rosserial**

```bash
rosrun rosserial_python serial_node.py _port:=/dev/ttyUSB0 _baud:=57600
```

> ⚠️ Replace `/dev/ttyUSB0` with the correct port if different on your system.

### 3. **Run the Keyboard Control Node**

```bash
rosrun robot_control ros_teleop_control.py
```

---

## 🐞 Troubleshooting

### ❗ Python Script Not Executable

If the Python file does not execute, make sure it has execute permissions:

```bash
chmod +x /home/<user>/catkin_ws/src/robot_control/scripts/ros_teleop_control.py
```

Replace `<user>` with your actual username.

---

## ⚙️ Auto Start Configuration (Optional)

This project includes an **auto-start setup** to launch everything automatically on system startup.

### 🔧 `auto_start.launch` (Located in the `launch/` folder)

```xml
<launch>
    <!-- Connect Arduino -->
    <node pkg="rosserial_python" type="serial_node.py" name="rosserial_arduino"
          args="_port:=/dev/ttyUSB0 _baud:=57600" output="screen" />

    <!-- Keyboard motor control -->
    <node pkg="robot_control" type="keyboard_control.py" name="keyboard_motor_control" output="screen" />
</launch>
```

> Make sure the port is correct: `/dev/ttyUSB0` might differ.

---

### 🧠 Autostart Application Entry

Create a startup entry using your OS's Startup Applications:

* **Name**: `Robot Project Autostart`

* **Command**:

  ```bash
  gnome-terminal -- bash -c "/home/$USER/start_robot.sh; exec bash"
  ```

* **Comment**: Start ROS, Arduino (rosserial), and keyboard control on login

---

### 📜 `start_robot.sh`

Place this script in your home directory (`~/start_robot.sh`) and make it executable:

```bash
#!/bin/bash

# Load ROS environment
source /opt/ros/noetic/setup.bash
source /home/$USER/catkin_ws/devel/setup.bash

# Launch the robot project
roslaunch robot_control auto_start.launch
```

Make it executable:

```bash
chmod +x ~/start_robot.sh
```

---

## 📌 Requirements

* ROS Noetic
* Arduino with compatible firmware
* Python 3
* `rosserial_python` package

---

