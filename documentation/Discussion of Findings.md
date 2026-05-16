### Time-domain behaviour
- Was the temperature stable over the 3 minutes?

The temperature readings showed a generally stable trend over the 3-minutes, with few values fluctuating within a narrow range, but only once right at the beginning and once right at the end. 

- Were there any sudden rises or drops?

There were no significant sudden rises or drops in the temperature readings. The signal appeared to have a relatively smooth progression without any major changes.

- Did the signal appear noisy?

No, the signal was very stable and did not appear to be noisy. The temperature readings were consistent and did not show significant random fluctuations.

### Frequency-domain behaviour
- Which frequency component had the highest magnitude?

Using Plot 2 that maps Magnitude vs Frequency, we can identify the frequency component with the highest magnitude. The dominant frequency component was at 0 Hz, with the highest magnitude in the entire graph at approximately 1500.

- Was the signal mainly low-frequency?

Yes, the signal was almost entirely low-frequency. The DFT plot showed that the majority of the energy was concentrated at the 0 Hz component. There were no significant peaks at higher frequencies, suggesting that the signal was dominated by low-frequency content.

- Did the DFT reveal any repeated pattern or periodic fluctuation?

No, the DFT in Plot 2 did not reveal any repeated patterns or periodic fluctuations, as it remained constant across the plot.

- Was there evidence of noise in higher-frequency components?

No, there was no evidence of noise in higher-frequency components. The DFT plot showed that the magnitude of the frequency components dropped off significantly after the 0 Hz component, indicating that there was minimal noise present in the signal.

### System behaviour
- Did the adaptive sampling strategy behave as expected?

Yes, the adaptive sampling strategy appeared to behave as expected. The temperature readings were consistent as temperature changes in the room tested in typically would happen slowly.

- Did the power mode selection appear sensible?

Yes, the power mode selection appeared sensible. The system switched to a lower power mode during long periods of stability, which is consistent with the observed stable temperature readings.

- Would you improve the system further?

I would start by reducing the time of each cycle before a power mode is decided, as the current 3-minute duration may be too long for certain applications. Additionally, I would consider implementing a more sophisticated noise reduction technique, such as a low-pass filter, to further enhance the signal quality, especially if the system is used in environments with more variable temperatures.

### Data quality
- Was the recording duration sufficient?

I think not, as a longer recording duration would provide more data points and allow for a better analysis of the temperature trends and system behavior over time.

- Was the sampling rate appropriate?

Yes, the sampling rate was appropriate for capturing the temperature changes in the environment. The data collected was sufficient to analyse the time-domain and frequency-domain behavior effectively.

- Were there any limitations in your measurement method?

One limitation of the measurement method is that it may not capture rapid temperature changes effectively if they occur within the 3-minute sampling window. Additionally, the system may not be suitable for environments with highly variable temperatures, as it may not respond quickly enough to changes. Finally, the current implementation does not account for potential external factors that could influence temperature readings, such as humidity or airflow, which could affect the accuracy of the measurements. Also, if the temperature sensor is blocked or covered, it may not provide accurate readings, which could impact the overall performance of the system.
