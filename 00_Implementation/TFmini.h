  if (Serial3.available()) {  //check if serial port has data input
	rx[i] = Serial3.read();
	if(rx[0] == 0x59) //header 
	{
		if(i == 8)
		{
			checksum = rx[0] + rx[1] + rx[2] + rx[3] + rx[4] + rx[5] + rx[6] + rx[7];
		}
		else
		{
			i++;
		}
	}
  }