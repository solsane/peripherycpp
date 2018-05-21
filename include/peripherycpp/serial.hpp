#ifndef _PERIPHERY_SERIAL_HPP
#define _PERIPHERY_SERIAL_HPP
#include <string>
#include <vector>
#include "peripherycpp/exceptions.hpp"
#include <memory>

extern "C"
{
    #include "serial.h"
}

std::map<std::string, bool> devices_open;
static bool isOpen(std::string device)
{
    if(devices_open.find(device) != devices_open.end())
    {
        return devices_open[device];
    }
    else
    {
        return 0;
    }
}

class Serial
{
public:
    /**
     * Default constructor
     */
    Serial();
    /**
     * Destructor
     */
    ~Serial();

    /**
     * Advanced open constructor
     * @param device   tty device at the specified path (e.g. "/dev/ttyUSB0")
     * @param baudrate baudrate device baudrate (ie, 115200).
     * @param databits databits can be 5, 6, 7, or 8
     * @param parity   parity can be PARITY_NONE, PARITY_ODD, or PARITY_EVEN
     * @param stopbits can be 1 or 2
     * @param xonxoff  software flow control settings
     * @param rtscts   hardware flow control settings
     * @brief Open the tty device at the specified path (e.g. "/dev/ttyUSB0"),
     * with the specified baudrate, data bits, parity, stop bits, software flow control (xonxoff),
     * and hardware flow control (rtscts) settings.
     */
    Serial(std::string device, unsigned int baudrate, unsigned int databits=8,
              int parity=0, unsigned int stopbits=1,
              bool xonxoff=0, bool rtscts=0);
    /**
     * open
     * @param device   tty device at the specified path (e.g. "/dev/ttyUSB0")
     * @param baudrate baudrate device baudrate (ie, 115200).
     * @param databits databits can be 5, 6, 7, or 8
     * @param parity   parity can be PARITY_NONE, PARITY_ODD, or PARITY_EVEN
     * @param stopbits can be 1 or 2
     * @param xonxoff  software flow control settings
     * @param rtscts   hardware flow control settings
     * @brief Open the tty device at the specified path (e.g. "/dev/ttyUSB0"),
     * with the specified baudrate, data bits, parity, stop bits, software flow control (xonxoff),
     * and hardware flow control (rtscts) settings.
     */
    void open(std::string device, unsigned int baudrate, unsigned int databits=8,
              int parity=0, unsigned int stopbits=1,
              bool xonxoff=0, bool rtscts=0);
    /**
     * read
     * @brief Reads len number of bytes via serial
     * @param  len        number of bytes to read
     * @param  timeout_ms length of timeout period in ms
     * @return            vector of bytes
     */
    virtual std::vector<uint8_t> read(size_t len, int timeout_ms);
    /**
     * buffer/c style alternative
     * @param buf        buffer to be read into
     * @param size       number of bytes
     * @param timeout_ms time before timeout
     */
    void read(uint8_t* buf, size_t size, int timeout_ms);
    /**
     * reads using a char* buf
     * @param buf        buffer to be read into
     * @param size       number of bytes
     * @param timeout_ms time before timeout
     */
    void read(char* buf, size_t size, int timeout_ms);
    /**
     * writes an array of uint8_t
     * @param data [description]
     */
    void write(uint8_t* data, size_t size);
    /**
     * write
     * @brief writes char* data
     * @param data vector of bytes to be written
     */
    void write(char* data, size_t size);
    /**
     * [write description]
     * @param data [description]
     */
    virtual void write(std::vector<uint8_t> data);

    /**
     * flush
     * @brief Flush the write buffer of the serial port.
     */
    void flush();

    /**
     * outputWaiting
     * @brief  Query the number of bytes waiting to be written from the serial port.
     * @return  the number of bytes waiting to be written from the serial port.
     */
    unsigned int outputWaiting();

    /**
     * inputWaiting
     * @brief  Query the number of bytes waiting to be read from the serial port.
     * @return  the number of bytes waiting to be read from the serial port.
     */
    unsigned int inputWaiting();

    /**
     * poll
     * @param timeout_ms  what it does depends on its value. If positive, it is a timeout in milliseconds. If 0, it is a non-blocking poll. If negative, it is a blocking poll.
     * @brief  Poll for data available for reading from the serial port.
     * @return  1 on success; 0 on timeout.
     */
    bool poll(int timeout_ms);

    /**
     * close
     * @brief  Close the tty device.
     */
    void close();

    /**
     * getBaudrate
     * @brief  Query the baudrate of the underlying tty device.
     * @return  the baudrate.
     */
    uint32_t getBaudrate();

    /**
     * getDatabits
     * @brief  Query the data bits of the underlying tty device.
     * @return  the number of data bits.
     */
    unsigned int getDatabits();

    /**
     * getParity
     * @brief  Query the Parity of the underlying tty device.
     * @return  an int representing the parity.
     */
    int getParity();

    /**
     * getStopbits
     * @brief  Query the stop bits of the underlying tty device.
     * @return  the number of stop bits.
     */
    unsigned int getStopbits();

    /**
     * getxOnxOff
     * @brief  Query the software flow control of the underlying tty device.
     * @return  a bool representing the software flow control.
     */
    bool getxOnxOff();

    /**
     * getRtscts
     * @brief  Query the hardware flow control of the underlying tty device.
     * @return  a bool representing the hardware flow control.
     */
    bool getRtscts();

    /**
     * setBaudrate
     * @param baudrate  the baudrate (used for setting on the tty device).
     * @brief  Set the baudrate on the underlying tty device.
     */
    void setBaudrate(uint32_t baudrate);

    /**
     * setDatabits
     * @param databits  the number of data bits (used for setting on the tty device).
     * @brief  Set the data bits on the underlying tty device.
     */
    void setDatabits(unsigned int databits);

    /**
     * setParity
     * @param parity  an int representing the parity (used for setting on the tty device).
     * @brief  Set the parity on the underlying tty device.
     */
    void setParity(int parity);

    /**
     * @brief Sets the stop bits for the transmission.
     * @param stopbits signals end to transmission frame, can be 1 or 2
     */
    void setStopBits(unsigned int stopbits);

    /**
     * setxOnxOff
     * @param enabled  a bool representing the software flow control
     * @brief  Set the software flow control on the underlying tty device.
     */
    void setxOnxOff(bool enabled);

    /**
     * setRtscts
     * @param enabled  a bool representing the hardware flow control.
     * @brief  Set the hardware flow control on the underlying tty device.
     */
    void setRtscts(bool enabled);
    /**
     * Reset. Closes and reopens the device.
     */
    void reset();
private:
    /**
     * checkError
     * @param err_code An int error code from Periphery Serial
     * @brief Acts as a error handler for the Serial class
     */
    void checkError(int err_code);

    serial_t m_serial;
    std::string m_device;
    unsigned int m_baudrate, m_databits;
    int m_parity;
    unsigned int m_stopbits;
    bool m_xonxoff, m_rtscts;
};

#endif
