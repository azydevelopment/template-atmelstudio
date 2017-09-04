#include "program.h"

#include <asf.h>

CProgram::CProgram() {
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
	/* Replace with your application code */
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