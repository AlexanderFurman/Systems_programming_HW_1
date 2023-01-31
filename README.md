./AsciiArtTool <flags> <source> <target>
 ./AsciiArtTool -i dog.txt inverted_dog.txt
 ./AsciiArtTool -e dog.txt encoded_dog.txt

# ASCII Art Compression Tool
This code allows the user to compress any text file using Run-Length Encoding with linked lists.
The user can also 'invert' the ASCII art.

## Usage
Run the following in the terminal:
```bash
./AsciiArtTool <flags> <source> <target>
```
```bash<flag>``` - indicates whether to compress (```bash -e```) or invert (```bash -i```) the image 
```bash<source>``` - name of the text file you wish to compress
```bash<target>``` - name of the text file which will be created after compression/inversion.

## Inversion Example

Given [dog.txt](https://github.com/AlexanderFurman/Systems_programming_HW_1/blob/main/tests/dog.txt):
 
```text
 /^ ^\
 / 0 0 \
 V\ Y /V
  / - \
 /    |
V__) ||
 ```
We can run:

```bash
./AsciiArtTool -i dog.txt inverted_dog.txt
```


Here's the output:

```text
@@/^@^\
@/@0@0@\
@V\@Y@/V
@@/@-@\
@/@@@@|
V__)@||
```

## Compression Example

Given [erling_haaland.txt](https://github.com/AlexanderFurman/Systems_programming_HW_1/blob/main/tests/erling_haaland.txt)
We can run:

```bash
./AsciiArtTool -e erling_haaland.txt encoded_haaland.txt
```
Here's an extract of the output:

```text
...

.9
 1
.107
,1
o1
d1
o2
l4
o4
d2
x3
k2
O1
04
K15
X13
K4
01
O2
01
k1
:1
.120

...
```
