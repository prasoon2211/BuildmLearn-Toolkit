import os
import datetime

def translate(filename):
	import pdb;pdb.set_trace()
	try:
		f = open(filename, 'rb')
	except Exception as e:
		return 0
	else:
		# operate on file
		# Dummy code
		# Open a new file in the same directory and write it with new
		# data. Return the filename to the calling c++ process
		dir_name = os.path.dirname(filename)
		ret_file = generate_filename(dir_name)
		ret_file = dir_name + os.sep + ret_file

		# Write to ret_file
		rf = open(ret_file, 'wb+')
		rf.write("Hello! This is a newly file created at " + str(datetime.datetime.now()) + " with old data: " + f.read())
		rf.close()
		f.close()
		# return filename to the called
		return ret_file

def generate_filename(dir_name):
	temp_name = "translatefile_"
	ret_file_name = None
	index = 0

	# See if file alreay exists - if so, change the index
	while not ret_file_name:
		if os.path.isfile(dir_name + os.sep + temp_name + str(index)):
			index += 1
		else:
			ret_file_name = temp_name + str(index)

	return ret_file_name