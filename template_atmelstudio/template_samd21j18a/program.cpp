#include "program.h"

#include <cstring>

/* PUBLIC */

CProgram::CProgram() :
	ILogger(),
	m_usart({}),
	m_enable_logger(false) {
}

CProgram::~CProgram() {
}

void CProgram::Main() {
	OnInit();

	while (1) {
		OnUpdate();
	}
}

void CProgram::OnInit() {
	/* Initialize the SAM system */
	system_init();
	
	InitLogger();
	
	struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);

	/* Configure LEDs as outputs, turn them off */
	pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PIN_PB30, &pin_conf);
	port_pin_set_output_level(PIN_PB30, true);

	/* Set buttons as inputs */
	pin_conf.direction  = PORT_PIN_DIR_INPUT;
	pin_conf.input_pull = PORT_PIN_PULL_UP;
	port_pin_set_config(PIN_PA15, &pin_conf);
}

void CProgram::OnUpdate() {

	Log("Hello world");
	
	while (1)
	{
		/* Is button pressed? */
		if (port_pin_get_input_level(PIN_PA15) == false) {
			/* Yes, so turn LED on. */
			port_pin_set_output_level(PIN_PB30, false);
			} else {
			/* No, so turn LED off. */
			port_pin_set_output_level(PIN_PB30, true);
		}
	}
}

// ILogger

void CProgram::InitLogger() {
	struct usart_config config;
	usart_get_config_defaults(&config);
	config.pinmux_pad0 = PINMUX_PA22C_SERCOM3_PAD0;
	config.pinmux_pad1 = PINMUX_PA23C_SERCOM3_PAD1;
	config.pinmux_pad2 = PINMUX_UNUSED;
	config.pinmux_pad3 = PINMUX_UNUSED;
	config.mux_setting = USART_RX_1_TX_0_XCK_1;
	config.baudrate = 9600;

	// wait until the usart has been initialized
	while(usart_init(&m_usart, SERCOM3, &config) != STATUS_OK);
	
	usart_enable(&m_usart);
	
	SetEnabledLogger(true);
}

void CProgram::SetEnabledLogger(bool enabled) {
	m_enable_logger = enabled;
}

bool CProgram::IsEnabledLogger() {
	return m_enable_logger;
}

void CProgram::LogEol() {
	if (m_enable_logger) {
		usart_write_wait(&m_usart, '\n');
	}
}

void CProgram::Log(const char text[], bool eol) {
	// TODO HACK: This probably isn't safe or efficient
	if (m_enable_logger) {
		// TODO HACK: C-style cast
		usart_write_buffer_wait(&m_usart, (const uint8_t*) text, strlen(text));
		if(eol) {
			LogEol();
		}
	}
}