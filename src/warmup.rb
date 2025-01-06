def fib(n)
  return [] if n== 0
  return [0] if n == 1

  sequence = [0,1]
  (2..n-1).each do |i|
    sequence << sequence[i - 1]+ sequence[i - 2] 
  end
  sequence
end

def isPalindrome(n)
     word_arr = word.downcase.gsub(/ /,'').split('')
  true if word_arr == reverse(word_arr)
end

def reverse(word_arr)
  reverse = []
  index = word_arr.length
  until index == 0 do
    reverse << word_arr[index - 1]
    index -= 1
  end
  reverse
end

def nthmax(n, a)
  # Check if n is within the valid range (0 to length of array - 1)
  return nil if n < 0 || n >= a.length

  # Sort the array in descending order
  sorted_array = a.sort.reverse


  # Return the nth largest value
  sorted_array[n]
end

def freq(s)
  # Initialize a hash to store character frequencies
  char_frequency = {}

  # Iterate through each chatacter in the input string 's'
  s.each_char do |char|
  # Increment the count for the current character in the hash
  if char_frequency.key?(char)
     char_frequency[char] += 1
  else
    char_frequency[char] = 1
  end
end


 # Initialize variables to keep track of the character with the highest frequency
  max_char = ""
  max_freq = 0

 # interate thorugh the hash to find the character with highest frequcny
 char_frequency.each do |char, freq|
   if freq > max_freq
     max_char = char
     max_freq = freq
   end
 end

 # Return the character with the highest frequcny
 return max_char
end

def zipHash(arr1, arr2)
  # Return nil if arrays are not of the same length
  return nil unless arr1.length == arr2.length
  # Create a hash by zipping the two arrays
  Hash[arr1.zip(arr2)]
end

def hashToArray(hash)
    hash.to_a
end
