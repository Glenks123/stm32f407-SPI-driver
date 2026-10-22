# SPI Master-Slave Communication with Logic Analyzer Verification

This project demonstrates full-duplex **SPI communication** between an **STM32 microcontroller** (Master, operating at 3.3V) and a **secondary microcontroller/board** (Slave, operating at 5V). A **4/8-Channel Bi-Directional Logic Level Shifter** bridges the voltage domains, and a **24 MHz 8-Channel USB Logic Analyzer** (Saleae Logic 2 software) captures protocol timing and frame exchanges.

---

## 1. Hardware Setup & Components

- **SPI Master:** STM32 Board (3.3V logic)
- **SPI Slave:** Arduino UNO (5V logic)
- **Voltage Translator:** Bi-Directional Logic Level Shifter (3.3V $\leftrightarrow$ 5V)
- **Logic Analyzer:** USB 24 MHz 8-Channel Logic Analyzer running Saleae Logic 2
- **Interconnects:** Breadboard, jumper wires, mini-USB / micro-USB cables

---

## 2. Hardware Connections & Pinout

### Logic Level Shifter Interconnects

| STM32 (Master - 3.3V) | Level Shifter (Low Side) | Level Shifter (High Side) | Slave (5V Domain) | Logic Analyzer Channel |
| :--- | :--- | :--- | :--- | :--- |
| **SPI_SCK** | LV1 | HV1 | Slave SCK | **Channel 0** (Clock) |
| **SPI_MOSI** | LV2 | HV2 | Slave MOSI | **Channel 1** (MOSI) |
| **SPI_MISO** | LV3 | HV3 | Slave MISO | **Channel 2** (MISO) |
| **SPI_CS / NSS** | LV4 | HV4 | Slave CS / SS | **Channel 3** (Enable) |
| **3.3V** | LV Power | — | — | — |
| **5V** | — | HV Power | 5V Power | — |
| **GND** | GND | GND | GND | GND |

---

<img width="1500" height="2000" alt="WhatsApp Image 2026-10-22 at 01 06 47" src="https://github.com/user-attachments/assets/cce02d50-27de-4b44-ae39-807a23a8c8c6" />

## 3. Logic Analyzer Capture & Protocol Verification

The communication frames are captured on **SPI[2]** in Saleae Logic 2 across four channels:

- **D0 (Channel 0):** `SPI[2] - Clock`
- **D1 (Channel 1):** `SPI[2] - MOSI`
- **D2 (Channel 2):** `SPI[2] - MISO`
- **D3 (Channel 3):** `SPI[2] - Enable` (Active Low Chip Select)

### SPI Data Packet Exchange Log

| Sequence | Enable Start | Duration | MOSI (Master Out) | MISO (Slave Out) | Status / Description |
| :---: | :---: | :---: | :---: | :---: | :--- |
| **1** | `4.964 s` | $3.875\ \mu\text{s}$ | `0x50` | `0x02` | Initial command send (`CMD_LED_CTRL`) |
| | | $3.875\ \mu\text{s}$ | `0xFF` | `0x50` | Dummy read / status exchange |
| **2** | `7.769 s` | $3.875\ \mu\text{s}$ | `0x50` | `0xF5` | Handshake ACK byte (`0xF5`) received |
| | | $3.875\ \mu\text{s}$ | `0xFF` | `0x50` | Buffer synchronization |
| **3** | `9.369 s` | $3.875\ \mu\text{s}$ | `0x50` | `0xF5` | Confirmed ACK response (`0xF5`) |
| | | $3.875\ \mu\text{s}$ | `0xFF` | `0x50` | Frame completion |

---

<img width="1200" height="565" alt="Screenshot 2026-10-22 010718" src="https://github.com/user-attachments/assets/96875e62-c8a2-40a6-97ce-b7d7e8094454" />
<img width="473" height="600" alt="Screenshot 2026-10-22 010735" src="https://github.com/user-attachments/assets/1512fa9f-2817-4126-9e21-031cd1b1e140" />


## 4. Key Protocol Takeaways

1. **Handshake Verification:** The slave validates the command code (`0x50`) sent by the master and acknowledges readiness with `0xF5` (ACK).
2. **Full-Duplex Transmission:** Simultaneous RX/TX shifting occurs over `MOSI` and `MISO` during each $3.875\ \mu\text{s}$ clock pulse train.
3. **Voltage Level Translation:** The bi-directional level shifter maintains signal integrity across the 3.3V and 5V logic thresholds without signal distortion.
