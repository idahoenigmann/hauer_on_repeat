## How does twelve tone music work? ##

To generate twelve tone music you follow an algorithm which takes the numbers
from one to twelve as an input. These numbers can be in any order as long
as each number appears only once.

Each number corresponds to a note from c (1) to h (12). These notes are
written into the twelve segments the piece will consist of. Each segment
should now consist of one note.

The next step is to fill in the segments, so that each segment is filled
with four notes (a four chord). This is achieved by grouping the notes
into four groups:
* 1, 2, 3 or c, c#, d
* 4, 5, 6 or d#, e, f
* 7, 8, 9 or f#, g, g#
* 10, 11, 12 or a, a#, b

Each note is repeated / copied into each following segment, unless another
note from the same group already is present in the segment, in which case
the new note will be pasted into the following segments.

From here on there are two possible ways to proceed: Monophony and Polyphony.
Since there is an algorithm that creates a Monophony, we choose Monophony over
Polyphony.

### Geometrical representation ###

After twelve segments the music starts at the first segment again. This
makes the timeline of twelve tone music a circle.

Note heights are not important in twelve tone music (c' is the same as c'')
Therefore after going up twelve half tone steps from c (= c') you reach
c (= c'') again. This makes the tone heights in twelve tone music a circle.

Combining these two geometrical shapes gives us a torus, representing the
music.
