# Introduction
The goal of the project was to create a robotic hand that is controlled by sensing the muscular contractions in the arm of the user and to replicate the movements on the robotic hand.


Electrodes will be placed on multiple areas on the arm of the user, and will sense the voltage differences of the muscles as they contract. The signal will be fed into a circuit which amplifies and filters the signal. The resulting signal will then be sent into the PIC32 microcontroller which will analyze the readings. An algorithm then decides which fingers should be moved and uses servos attached to each finger of the hand to move the fingers. 

# High Level Design
## Rationale and Sources of Project Idea
The inspiration for the project came from an interest in the biological signals being triggered in our bodies and how they control different body parts. We wanted to better understand the signals sent to nerves and muscles in our bodies and how we can actually pick up these signals. Currently, much research is done on neural interfaces between humans and machines so we thought an interesting and applicable project would be to control a robotic hand by just using nerve impulses. As a person’s hand moves, the various muscles in the arm contract. We wanted to analyze the signals sent to muscles in the arm and replicate the hand’s motions onto a robotic hand.

## Logical Structure & Setup Approach
To read the muscle contractions in the arm, surface electromyography (EMG) techniques was used. Electrodes were placed on two areas on the underside of the arm to read the electrical signals. These places were chosen by empirical estimates, as they produced the greatest muscle contractions when the fingers were pressed. Since the electrodes are placed on the surface of the skin, the signal strength is very weak (~2mV at best) and noisy.


To improve the signal, the signal was fed into an instrumentation amplifier, followed by a high pass filter, a differential amplifier, and finally a low pass filter. The amplified and filtered signals were then fed into Analog to Digital Converters on the PIC32 microcontroller. If certain conditions were met, a finger was determined to be pressed, and servos would pull a string attached to a finger of the robotic hand to contract it. 


For the software design, the high level logical structure for the program flow is given by the following: 
![Program Flow](images/Cyborg ( Timer ISR Code ).png)  
*Logical structure for the software implementation*


As the above flowchart indicates, we read the input value, do some processing and detection based on the input and move the actuator(servo) based on the detection algorithm. This completes the high level software and hardware description.


## Hardware/Software Tradeoffs
Since neurons generally fire between 0-500 Hz, a sampling speed of 500 Hz was used for the ADC. This meant that new signal readings were coming in once every 1/500 of a second and the software would need to process and be ready for a new value within that time. Since 500 Hz is a relatively small sampling speed, both hardware and software components were able to process successfully within that time. 


To optimize the project even more, we tried to balance the hardware and software sides. To do so, we added a sliding moving averager within software that basically acts like a crude low pass filter since it smoothes out the signal and cuts out higher frequencies. This produced a more consistent and steady signal reading instead of the rapidly oscillating signal coming in directly into the ADC from the electrodes. 
We also made a design tradeoff by using a cutoff for the high pass filter to be around 72 Hz, so that we had a better elimination of the 60 Hz line noise, at the expense of losing some signal data at these frequencies. 


We also made a design tradeoff by using a cutoff for the high pass filter to be around 72 Hz, so that we had a better elimination of the 60 Hz line noise, at the expense of losing some signal data at these frequencies. 

## Relationship of prject design to available IEEE, ISO, ANSI, DIN, and other standards.
No standards from IEEE, ISO, ANSI, or DIN were used.
  
## Existing patents, copyrights, and trademarks relevant to project. 
No patents, copyrights, or trademarks are relevant to the project as all circuits and software was designed by us. 



# Program/Hardware Design
## SOFTWARE DESIGN
### ADC
The ADC has two functions: sampling & conversion. The sampling rate for the ADC is set by using a clock divider and changing sample hold time for the ADC. All this is controlled in the initial configuration of the ADC. The ADC is configured to auto sample and convert. We also scan two analog input values (AN2 and AN3), from two different electrodes. The conversion results are placed in ADC buffer 0 and buffer 1. The ADC clock is around 588 kHz. 


However, we do not get samples at 588 kHz, as most EMG signals have a frequency range of 5-150 Hz. So we use Timer2 ISR to read ADC buffer values at a predetermined sample rate. We experimented with different sampling rates and found that 500 Hz was good enough for the signal to not have any aliasing. In order to do this, we set the prescaler to 16, and loaded the timer with a value of 50,000. Most of the filtering is done in the ISR. The configurations that were set up for the peripherals involved are summarized in the diagram below: 


![Configurations](images/Cyborg(Configurations).png)  
*ADC, OC, & Timer Configurations*


### Averager
The purpose of the averager is to smoothen out the incoming ADC readings to produce a more consistent signal. Since our body signals contain many oscillations, the input reading to the ADC also contains many oscillations. By using a sliding window averager, the newest signal reading is averaged with the last 127 readings to produce a signal with less variations.


The averager keeps track of the last 127 ADC readings by using a 127x2 matrix called input_history. The first column of the matrix corresponds to electrode pair 1 and the second column corresponds to electrode pair 2. The row corresponds to the nth previous reading. Every time a new voltage is read by the ADC, the ISR calls the averager function to determine the average of the previous readings plus the new reading. It does so by adding all elements in a column of the matrix and then adds the newest ADC reading. It then divides the summation by 128 and sets the result as the filter output, which is sent back to the thresholding function to be analyzed. 


To update the input_history matrix, the averager function sets the j-1 element of the matrix to the jth element and sets the 0th element to the newest ADC reading. 


![Averager](images/Cyborg ( Averager ).png)  
*LEFT:   Flowchart for the averager implementation*  
*RIGHT:   Flowchart for updating history values*


### Region Detection (Thresholding) 
We use two electrodes to detect 5 fingers. Each electrode input has an ADC range of 0-1024. So we can represent the total input space as a 2D square space of size 1024x1024. We then empirically measure the block regions that each finger can correspond to. Even though the relative strengths of different fingers remain the same across different people or environments, the magnitudes themselves were people and environment dependent. 


Noise plays a role in determining the regions in the 2D space for different fingers. In order to minimize the noise, we made sure the wires were twisted together tightly; there was no direct power supply from an AC power socket; and we were in an environment of low light away from the 120Hz frequency influence of the above fluorescent bulbs. Even though we were not able to completely eliminate noise, we tried to minimize it as much as we could. We then did empirical estimates for different finger regions by looking at ADC read values in PuTTy. The resulting regions for different fingers is seen in the diagram below:


![Thresholds](images/Thresholds.JPG)  
*Finger Regions based on Electrode Inputs*  


We did addition checking for consistency in these threshold regions to activate a finger movement. We created an array variable called changes which keeps track of the number of times the ADC inputs have been encountered in any of the finger regions. We also created an array variable called finger_state, which is set to 1 if a particular finger is pressed. In our current program, we constrain it such that only one finger can be pressed at a time, as multiple finger detection would require more electrodes and more complexity. 


If this number of changes crosses an upper threshold for the finger, we mark that finger as being pressed. Similarly, to measure if a particular finger is released, we decremented the changes variable for a finger if it was outside the finger’s region. If this value goes below a lower threshold, we identify the finger as being released. This is seen just an implementation of hysteresis for the finger input, so that the finger does not rapidly fluctuate up and down due to random noise fluctuations. 


We chose to move only one finger at a time. This is done by using constraining only one finger’s state to be pressed at any given time. This is done so that the complexity of our project is reduced. If many finger movement is to be implemented, we would have to use more electrodes and find move innovative ways to isolate regions for combination of fingers. 


The flowchart for the finger region identification and hysteresis is shown below:


![Threshold Flowchart](images/Cyborg ( Finger Thresholding ).png)  
*Region Identification & Hysteresis flowchart*  


### Servo Movement
To control the fingers on the robotic hand, servos attached to string manually pull the fingers down when the servos swing 180 degrees. To control the servos, PWM waves sent to the servo determine which angle the servo points to. For example, when the signal is high for 0.54 ms, the servo is at 0 degrees. When the signal is high for 2.5 ms, the servo points to 180 degrees.


Since operating servos requires a 50 Hz PWM wave and the PIC32 clock cycle is at 40 MHz, or 40*10^6 ticks per second, 40*10^6 / 50 = 800,000 ticks per period. Since 800,000 overloads the timer, a prescaler of 16 was used. Therefore, 800,000/16 = 50,000 ticks/period with a prescaler of 16. It was found that to get the servos to point to 0 degrees, 1,350 of the 50,000 ticks need to be high. For the servos to point to 180 degrees, 6,250 ticks would need to high out of the total 50,000. Loading the PWM function of the PIC32 with the number of ticks that need to be high during one period allowed us to successfully output PWM waves and control the angle which the servos were pointing at. 


### Servo Lock
Each servo has a finite time to rotate by 180 degrees. We empirically estimated this value to be 600 ms. We had to make sure that no other servo moved when another finger servo was moving, and make sure not to change the state of a particular finger unless 600 ms has passed. Both of these conditions were met by implementing a variable called lock_motor. Initially lock_motor is set to 0 when no finger servo is moving. If there is a change of state and if no other servo is moving, we set lock_motor to the current finger digit and make sure that no other finger moves unless this finger servo resets the lock_motor value back to 0. This is not done for at least 600 ms. Thus, by introducing this variable, we ensure that two finger servos do not move at the same time.  The flowchart for this implementation is given below:


![Servo Lock](images/Cyborg ( Move Finger ).png)  
*FINGER SERVO MOVEMENT:  Flowchart for making sure only one finger servo moved at a given time*  


## HARDWARE DESIGN:
### Hand Design
The hand itself was ordered pre-made from Amazon: [4m Robotic Hand Kit](https://www.amazon.com/4M-3774-Robotic-Hand-Kit/dp/B005MK0OPO). Each finger is attached to a piece of fishing line which, when pulled, causes the finger to contract. We attached a board at the base of the hand and mounted five servo motors on it, one for each finger. The wires pulling each finger were attached to a servo. In order to move a finger the servos rotate 180 degrees, pulling the wire and bringing the fingers from extended to contracted. 


![Robotic Hand](images/Servos.png)  
*Hand and servo motor setup*


### Electrodes
In order to differentiate the signals between the different fingers, we used two sets of two electrodes on the forearm, all referenced to the same ground. For both sets, the two electrodes were placed about a quarter to a half an inch apart and affixed to the arm of the user with tape or foam sticking pads. 


![Electrode Placement](images/Electrode Placement.JPG)  
*Electrode placement markings. The ground electrode was placed on the wrist.*


When a muscle receives a signal from the nervous system, it triggers an action potential in the muscle cell, essentially just a voltage difference across the cell membrane. An attenuated version of these voltage differences can be measured on the surface of the skin, after passing through the dielectric medium of veins, body fat, and skin. The action potentials occur at varying frequencies depending on the strength of contraction of the muscle. 


The Silver Chloride (AgCl) electrode consists of a silver electrode. A conductive gel containing Chloride ions is applied to the electrodes before they are attached to the skin. When a muscle in the vicinity of an electrode fires an action potential, it can be detected as a current of chloride ions on the skin. The chloride ions bind to a Silver atom and “knock off” an electron (the reverse reaction happens as well). The electron can then travel through a wire connected to the electrode as a normal current. 


![Electrode](images/Electrode.JPG)  
*A Silver Chloride electrode*


In order to get a good signal, the electrodes had to placed over the belly of the muscle being read. If the electrodes are placed close to the tendons, the signal will be inconsistent and will not accurately reflect the activity of the muscle. Furthermore, there are several muscles in the forearm in close proximity to one another. This makes it difficult to isolate a signal from only one muscle. In order to differentiate between the different inputs generated by different fingers, we measured the same group of muscles at two different locations. The variable activity between these two inputs allowed us to discriminate between the signals generated by the contraction of different fingers. 


### Instrumentation Amplifier & Bandpass Filter Design
The signal detectable on the surface of the skin should theoretically be around 2mV, but we found it to be significantly less in practice to be around 10 uV. In order to read this signal, we designed an instrumentation amplifier.  Because the resistance of a human body is fairly high, on the order of Megaohms, the input impedance of the amplifier needed to be significantly higher. The instrumentation amplifier design is characterized by extremely high input impedance, low noise, and high common mode rejection. This was ideal for our purposes as combating noise was our most significant challenge during this project. The basic design of the instrumentation amplifier was derived from the schematic in Medical Instrumentation: Application and Design, although we changed the specific resistor and capacitor values. The amplifier we built contains two input op-amps along with a two stage differential amplifier. The gain of the first stage was 25, and the gain of the second stage was 214, for an overall gain of 5350. The amplifier contains high and low-pass filters, which are intended to reduce the signal received to the frequency ranges that were relevant to us. The low-pass filter has a cutoff frequency of ~1500Hz, and the High-pass filter has a cutoff of 72Hz. This was aimed at eliminating 60Hz line noise. 


![Schematic](images/Bandpass_amplifier_simulation.png)  
*Instrumentation amplifier simulation schematic. 
(Note: the actual op-amps used in the circuit were LF353, not LM358.  Unfortunately the design software does not have these as an option. However, the results were are good estimates of the actual design )*


The final circuit contained two of these amplifiers, one for each of the two sets of electrodes. Running the circuit simulation, the oscilloscope output was seen to be:


![Oscilloscope](images/Oscilloscope.png)  
*Oscilloscope output: The input amplitude is 20 uV, and the output amplitude is 160 mV approximately. We see that we at least have a good enough gain to measure, as the ADC resolution is 3.3/1024 = 3.2 mV.*


The bandpass filter is seen in the diagram below:


![Band Pass Filter](images/Bode_plot_magnitude.png)  
*Bode Plot Viewer:  The plot shows a bandpass filter that has a peak gain of 80.561 dB at around 265 Hz.*


### Failed Approaches
#### Butterworth Filter
The moving averager was still not consistent enough to smooth out the fluctuations. So we tried using a butterworth lowpass filter to smooth out the high frequency fluctuations by using as little coefficients as possible. However, we found that the filter we wanted to implement still did not eliminate the noise levels we wanted. If we remedied the above by using a low cutoff frequency and a high pole filter, we faced the problem of having a slow rise time for the filtered signal. Thus we abandoned the above approach. 


#### Neural Network
Neural network was very promising initially. We were able to predict individual fingers with good probabilities at certain instances. However, surface EMG is such a noise dependent measurement, that it the network has to be trained every time the person or the environment is changed. Even with this being an obstacle that can be overcome, there needs to be more hidden layers in the network to get more accuracy with more training data. With a single layer of 20 nodes, we used 500 us. The computation time increases exponentially with more layers. This can be remedied by using external flash memory, but we abandoned that decision by our budget constraints. 


#### Differential OpAmp
Before using the instrumentation amplifier design, we attempted to do a simple two stage differential amplifier. This was somewhat sufficient, but quite noisy. The impedance of the amplifier was of the same order of magnitude as that of the user. This caused the amplifier to be very poor. 


#### Isolating each finger based on muscle location
The original plan for discriminating between different finger inputs was to locate the muscle responsible for contracting each finger and attach a set of electrodes to it. This proved too difficult as the muscles in the forearm are close together and some are buried beneath others. 



# Results
## Finger Input Ranges
For one noise free environment, we found the different finger ranges in the 2D generated by the 2 electrode inputs (1024x1024) to be:


![Thresholds](images/Thresholds.JPG)  
*Range of voltages each finger on both sets of electrodes*


## Bandpass Filter & Gain Circuit
![Circuit](images/Gain_Filter Circuit.JPG)  
*Hardware circuit layout used*


## Finger Movement Capture
![Finger Diagram](images/Five fingers isolated.png)  
*Isolating each of the five fingers*


## Demo
[![Demo](https://img.youtube.com/vi/kEv7I8N3MB8/0.jpg)](https://www.youtube.com/watch?v=kEv7I8N3MB8&t=87s)

## Five Finger Test
[![Five Finger Test](https://img.youtube.com/vi/Lsh_Z_aI9V8/0.jpg)](https://www.youtube.com/watch?v=Lsh_Z_aI9V8)

### Numeric
The internal 10-bit ADC was used in our design. This has 1024 values with the highest value corresponding to 3.3 V. Thus the resolution of the ADC is 3.2 mV. Moreover, since the ADC is not accurately calibrated, this range was reduced and hence we had a lower voltage range to work with. This was however not a serious limitation as our input signals were in the order of a few hundred mVs. 


The moving average filter used fix16 variables so that computation time can be saved in comparison to floating point arithmetic. 


### Timing
A Timer ISR was used to read the ADC buffer values at a fixed rate of 500 Hz. Since filtering was done at every ADC buffer read, we had to make sure that the computation time was less than 1/500 s = 2 ms. We used an other timer to measure the time of execution for the whole filter and region detection algorithm. We found that even if a single 20 neuron hidden layer neural network was implemented, the computation time did not exceed 500 us. Thus we has ample excess time to use in the ISR id needed. We see that this timing constraint is satisfied.  


### Bandwidth
Surface EMG signals have a bandwidth of 5-500 Hz. However, the most prominent signals are within 5-150 Hz, with only a few signals rarely exceeding this range. Our hardware design at least accommodates a major part of this frequency range. Moreover, the sampling rate is 500 Hz, which gives a Nyquist frequency of 250 Hz. The most prominent frequencies are still within this range. This the bandwidth constraint was satisfied. 


### Noise Sources
Noise sources are major deterrents in using surface EMG. We tried to study as much noise sources as we can and eliminate sources when we can, without using extreme measures. 


One of the most dominant noise sources is the 60 Hz line noise. We eliminated this by using isolated power supplies. The 60 Hz line noise can also be introduced on the body when there are power sockets in the vicinity. Thus was partially remedied by using using the high pass filter with a cutoff at 72 Hz. Another source of noise is from the fluorescent light bulbs. They flicker at twice the line frequency, and all the odd harmonics of this noise can be induced on the human body. We just tried to reduce this by trying to do measurements in places not directly under fluorescent bulbs. 


Another source of noise that we observed is the interference from other muscles in the proximity. Not just the muscles in the hand, but the muscles in the chest and so on. This can be reduced by stretching the hand far away from the body as possible. Precaution should be taken to make sure that the two polarities within an electrode pair do not touch. This would create an unpleasant sting and also cause a leakage current which will obscure the electrode signal. 


Magnetic coupling that is induced in the wires from external sources should also be considered. Any current carrying wire loop has an inductance associated with it. This causes magnetic field coupling that induces some noise current in the circuit. This is reduced by using twisting the wires together and making sure the length of the wires is not too long. This ensures that the inductance of the wires is at a minimum, and hence the magnetic coupling is at a minimum.  


## Safety considerations in the design
In order to enforce safety, we designed the entire circuit to be completely isolated from any 110V outlets. Theoretically, if there had been a pathway to 110V ground somewhere in the circuit and the test subject were to somehow touch the hot wire of an outlet, he could be seriously injured or killed. 


Another possible issue could arise if the circuit were connected to two different outlets with different grounds. If the test subject is connected to some electrical equipment from one outlet and some other equipment from another outlet which is referenced to a different ground, this could cause there to be a voltage across the test subject.  If the voltage is large enough, or if the subject’s heart is weak enough, this could potentially cause the heart’s pacemaker to become irregular, leading to cardiac arrest. 


Isolating the entire circuit eliminates these issues.  In order to test the circuit safely we wrote a simple program for an arduino to be used as an oscilloscope, as connecting the circuit to a normal oscilloscope would have created a path to ground. We were then able to use a laptop running on battery power (isolated from ground) to measure signals. 


A secondary issue we discovered was that the conductive gel that we applied to the electrodes would occasionally get in between the electrodes and create a short, leading to the user feeling a slight tingling sensation. In order to eliminate this issue we applied the gel more judiciously and made sure that the space between electrodes was clean and dry at all times. 


## Usability
The project has implications for a number of different possible functions. Amputees could potentially use a similar device to regain the functionality of a lost limb. Furthermore, the input could be measured and analyzed locally and transmitted to a remote device which would respond accordingly. This could have applications with regard to performing surgeries or possibly military technology. 


In its current form, all that is required for any user is an arm with intact forearm muscles. The device must be calibrated for each user. The setup is completely non-invasive, making it an attractive and simple option for all users. 


# Conclusions
Our design met our expectations and goals set at the beginning of the project. Our goal was to use solely electrode inputs to mimic on a robotic hand the movements of our own hand. At the end of the project, we were able to isolate the signals for each finger and move all five fingers independently of each other on the robotic hand. Judging the design of our circuits, we were able to provide enough gain in the amplifier circuit for us to convert the signal from a few μV in amplitude to one that is a few volts large and readable by the ADC. We were also fairly successful in filtering out unwanted noise so that the signal we received was more accurate. 


We could potentially add extra functionality to the hand such as the ability to sense multiple fingers being pressed at the same time. Another way to improve the project would be to improve the responsiveness of the fingers and have them move with little delay when compared to our own hand. This may mean playing around with the thresholds and increment/decrement values so that the fingers move more quickly. 


## How did your design conform to the applicable standards?
No standards are applicable to our design.


## Intellectual property considerations
Since all parts of our project was designed by us, we did not use any other sources of intellectual property. As for considering obtaining intellectual property rights, we don’t mind sharing our designs and code with the public.


## Potential Opportunities
We believe if we improve our project and add more advanced capabilities, there may be patent opportunities or publishing opportunities for our project. For example, using a more robust and custom made robotic hand with gripping capabilities or improving the algorithms thresholding capabilities to adapt to users more quickly and accurately. 


## Ethical Considerations
Over the course of the project, from design of the circuit to writing the software, we followed all aspects listed within the IEEE Code of Ethics. We made sure the product was safe and would not cause any harm to the user. Since we used electrodes which make direct body contact with the user, we made sure all procedures taken would be safe. This meant using a single common ground, making sure multiple electrodes are separated and not shorted, and using stand alone 9V batteries. To analyze the waveforms, we understood using an external oscilloscope would be hazardous since it did not share a common ground with our circuit. To circumvent this, we used an oscilloscope script running off an Arduino that shared a common ground with our circuit.


All the results and designs listed in the report and used during the demo of the project were authentic and were not taken from elsewhere. All the data collected and all the graphs simulated were based off our own project designs and are in agreement with the IEEE Code of Ethics. Over the course of the project, no bribes were taken and there were no forms of discrimination based on based on race, religion, gender, disability, age, national origin, sexual orientation, gender identity, or gender expression.


# Appendix A
The group approves this report for inclusion on the course website.  

The group approves the video for inclusion on the course youtube channel.


# Appendix
## Schematic
![Schematic](images/Bandpass_amplifier_simulation.png)  


## Cost Breakdown
![Cost Breakdown](images/Cost Breakdown.png)  


## Task Breakdown
**Michael:** Researched EMG usage and placement, built instrumentation amplifier circuit, assembled hand and servos, tested EMG signals, helped write code for finger discrimination thresholding


**Jason:** Servo control, built instrumentation amplifier circuit, tested EMG sensors, helped calibrate thresholds, helped write code for finger discrimination thresholding, created website


**Krishnaa:** Wrote ADC code, wrote ISR, helped write finger discrimination thresholding code, wrote locking code to differentiate between fingers, researched instrumentation amplifier

