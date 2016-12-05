### Introduction
The goal of the project is to create a robotic hand that is controlled by sensing the muscular contractions in the arm of the user and replicate the movements on the hand.   

Electrodes will be placed on multiple areas on the arm of the user that sense the voltage differences of the muslces as they contract. The electrode signals will be sent into a gain and filter circuit which amplifies and cleans the signal to be passed into the analog digitial converter (DAC) of the PIC32 microcontroller. The PIC32 will then analyze the inputs and decide which fingers, if any, were moved. The PIC32 will then send PWM waves to move the servos attached to the robotic hand and move the fingers.  

### High Level Design
rationale and sources of your project idea

background math

logical structure

hardware/software tradeoffs

Relationship of your design to available IEEE, ISO, ANSI, DIN, and other standards.

Discuss existing patents, copyrights, and trademarks which are relevant to your project.


### Program/Hardware Design
program details. Could someone else build this based on what you have written?

hardware details. Could someone else build this based on what you have written?

Be sure to specifically reference any design or code you used from someone else.

Things you tried which did not work

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
