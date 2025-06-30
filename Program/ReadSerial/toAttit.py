import serial
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# === 串口設定 ===
SERIAL_PORT = '/dev/cu.usbserial-10'       # ⚠ 改成你實際的 COM port (Windows) 或 /dev/ttyUSB0 (Linux)
BAUD_RATE = 115200

def euler_to_rotation_matrix(pitch, roll, yaw):
    # 歐拉角轉成旋轉矩陣 (Z-Y-X: yaw → pitch → roll)
    pitch = np.radians(pitch)
    roll = np.radians(roll)
    yaw = np.radians(yaw)

    Rx = np.array([
        [1, 0, 0],
        [0, np.cos(roll), -np.sin(roll)],
        [0, np.sin(roll),  np.cos(roll)]
    ])
    Ry = np.array([
        [np.cos(pitch), 0, np.sin(pitch)],
        [0, 1, 0],
        [-np.sin(pitch), 0, np.cos(pitch)]
    ])
    Rz = np.array([
        [np.cos(yaw), -np.sin(yaw), 0],
        [np.sin(yaw),  np.cos(yaw), 0],
        [0, 0, 1]
    ])
    return Rz @ Ry @ Rx

def draw_orientation(ax, R):
    # 原本的 XYZ 軸
    origin = np.array([0, 0, 0])
    axis_length = 1.0
    axes = np.eye(3) * axis_length

    # 旋轉後的 XYZ 軸
    rotated_axes = R @ axes

    colors = ['r', 'g', 'b']
    labels = ['X', 'Y', 'Z']

    for i in range(3):
        ax.quiver(
            *origin, *rotated_axes[:, i],
            color=colors[i], label=f'{labels[i]}-axis', length=1.0, normalize=True
        )

def main():
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"Connected to {SERIAL_PORT}")

    plt.ion()
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    while True:
        try:
            line = ser.readline().decode().strip()
            if not line:
                continue
            parts = line.split(',')
            if len(parts) != 3:
                continue

            pitch, roll, yaw = map(float, parts)

            R = euler_to_rotation_matrix(pitch, roll, yaw)

            ax.cla()
            ax.set_xlim([-1, 1])
            ax.set_ylim([-1, 1])
            ax.set_zlim([-1, 1])
            ax.set_xlabel('X')
            ax.set_ylabel('Y')
            ax.set_zlabel('Z')
            ax.set_title(f"Orientation (Pitch={pitch:.1f}°, Roll={roll:.1f}°, Yaw={yaw:.1f}°)")

            draw_orientation(ax, R)

            plt.draw()
            plt.pause(0.01)

        except Exception as e:
            print(f"Error: {e}")

if __name__ == '__main__':
    main()