Wanted own lib folder but didnt get it to work with vscode mplab extention

Q3:
The approach that utilizes polling with sleep mode standby is clearly more energy efficient. On the other hand, it is slightly more complex to implement and has a bit higher latency due to sleep mode wakeup time and only checking on a set interval. The polling method is also preffered as the cpu is only interrupted every once in a while and not every loop so if one would need a different process with lower latency running constantly this is a possibility.

Q4:
The interrupt driven approach is the most energy efficient as the CPU can remain in sleep mode until an event occurs that requires its attention. This minimizes power consumption during idle periods. However, the interrupt will stop other processes from running while the interrupt is being serviced, which can introduce latency for other tasks. For this certain application though this is not really an issue.

Q5:
This approach is very energy efficient as the CPU can remain in sleep mode while the event system handles the communication between peripherals. This method would also free up CPU resources completely for other tasks if needed.

Q6:
I have used the builtin Github copilot in vscode to write out code explanations faster, as it finishes sentences for me once the code is alraedy writen.

I didn't use any AI for any code generation as setting registers in the microcontroller correct was more reaserch based (reading the datasheet and knowing wich resisters/bits to set high) and I felt the AI was just in the way if I didn't have it snoozed. The datasheet to the avr db-family felt sufficient for explanations and the built in "macros" in VSCode for setting the registers made it so that you can serch using the mplab extention once you knew the correct setup routine to implement. 
