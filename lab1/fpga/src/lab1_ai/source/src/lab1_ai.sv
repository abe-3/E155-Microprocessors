module lab1_ai(
	output logic led_out // Output to drive the LED
);

// --- Internal Signals ---
    logic clk_48mhz; // Clock signal from the internal oscillator

    // --- Parameters ---
    // Constant for the counter's maximum value to achieve a 2Hz blink
    // A 2Hz blink means the LED state must toggle every 0.25 seconds (4Hz toggle rate).
    // COUNTER_MAX = (48 MHz) / 4 Hz = 12,000,000
    localparam int COUNTER_MAX = 12_000_000;

    // --- Instantiate Internal High-Frequency Oscillator ---
    // This is the Lattice iCE40 specific primitive for the 48MHz oscillator.
    // The HSOSC primitive is configured to be always enabled and pulled-up.
    HSOSC i_hfosc (
        .CLKHFEN (1'b1),      // 1'b1: High-frequency oscillator is enabled
        .CLKHFPU (1'b1),      // 1'b1: High-frequency oscillator pull-up is enabled
        .CLKHF   (clk_48mhz)  // Output clock at 48MHz
    );logic int_osc;


    // --- Clock Divider and LED Toggle Logic ---
    // A counter is used to divide the 48 MHz clock down to our target frequency.
    // The counter needs to be large enough to hold COUNTER_MAX.
    // 2^23 = 8,388,608
    // 2^24 = 16,777,216 -> so we need at least 24 bits.
    logic [23:0] counter = 0;

    // Use a synchronous process (always_ff) for the counter.
    // This process triggers on every rising edge of the 48MHz clock.
    always_ff @(posedge clk_48mhz) begin
        if (counter == COUNTER_MAX - 1) begin
            counter <= 0;         // Reset the counter
            led_out <= ~led_out;  // Toggle the LED output
        end else begin
            counter <= counter + 1; // Increment the counter
        end
    end
endmodule