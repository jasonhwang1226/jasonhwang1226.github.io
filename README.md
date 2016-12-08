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


As the above flowchart indicates, we read the input value, do some processing and detection based on the input and move the actuator(servo) based on the detection algorithm. This completes the high level software and hardware description.


## Hardware/Software Tradeoffs
Since neurons generally fire between 0-500 Hz, a sampling speed of 500 Hz was used for the ADC. This meant that new signal readings were coming in once every 1/500 of a second and the software would need to process and be ready for a new value within that time. Since 500 Hz is a relatively small sampling speed, both hardware and software components were able to process successfully within that time. 


To optimize the project even more, we tried to balance the hardware and software sides. To do so, we added a sliding moving averager within software that basically acts like a crude low pass filter since it smoothens out the signal and cuts out higher frequencies. This produced a more consistent and steady signal reading instead of the rapidly oscillating signal coming in directly into the ADC from the electrodes. 


We also made a design tradeoff by using a cutoff for the high pass filter to be around 72 Hz, so that we had a better elimination of the 60 Hz line noise, at the expense of losing some signal data at these frequencies. 

## Relationship of prject design to available IEEE, ISO, ANSI, DIN, and other standards.
No standards from IEEE, ISO, ANSI, or DIN were used.
  
## Existing patents, copyrights, and trademarks relevant to project. 
No patents, copyrights, or trademarks are relevant to the project as all circuits and software was designed by us. 



# Program/Hardware Design
## program details. Could someone else build this based on what you have written?

## hardware details. Could someone else build this based on what you have written?

## Be sure to specifically reference any design or code you used from someone else.

## Things you tried which did not work

### Results
This is the section which is most often lacking in student projects. Be specific! 

If you took calibration data, then show it!

If you have images or video, include it.

speed of execution (hesitation, filcker, interactiveness, concurrency)

Be quantitative. Show graphs!

accuracy (numeric, music frequencies, video signal timing, etc)

Be quantitative. Show graphs!

how you enforced safety in the design.

interference with other people's designs (e.g. cpu noise, RF interference).

usability by you and other people (perhaps with special needs).

### Conclusions
Analyse your design in terms of how the results met your expectations. What might you do differently next time?

How did your design conform to the applicable standards?

Intellectual property considerations.

Did you reuse code or someone else's design?

Did you use code in the public domain?
Are you reverse-engineering a design? How did you deal with patent/trademark issues.

Did you have to sign non-disclosure to get a sample part?

Are there patent opportunites for your project?

Are there publishing opportunities for your project?

Ethical considerations. Refering to the IEEE Code of Ethics, specifically explain how decisions you made or actions you took in this project were consistent with this Code of Ethics. I expect at least 200 words on this topic. A bulleted list will not be acceptable.
Legal considerations. For instance, if you use a transmitter, you must discuss the appropriate FCC legal restrictions.

### Appendix A
The group approves this report for inclusion on the course website.

The group approves the video for inclusion on the course youtube channel.

### Appendix
Appendix with commented program listing

Appendix with schematics (you can download free software from expresspcb.com to draw schematics) 

A block diagram is not a schematic.

Appendix with cost details with all part numbers, vendors, and their price. This cost will include components as described in the Budget Considerations section.

Appendix with a list of the specific tasks in the project carried out by each team member.

### References
Data sheets

Vendor sites

Code/designs borrowed from others

Background sites/paper
