#ifndef REGGIE_STREAM_H
#define REGGOE_STREAM_H

#include <stdlib.h>
#include <stdbool.h>

// a structure to represent a stream of data
struct stream {
	// get a pointer to the next value in the stream
	void *peek(struct stream s);

	// advance the stream to the next value
	// returns a stream object that will be able to peek to the next value
	struct stream advance(struct stream s);

	// is there any more data in the stream?
	// returns true if there is no more data in the stream
	bool closed(struct stream s);

	// a pointer to any arbitrary data
	// default functions assume this is an array
	void *data;

	// the size of each element in the data array
	size_t part_size;

	// the total amount of elements in the data array
	size_t length;
};

typedef void *(*peek_fn)(struct stream);
typedef struct stream (*advance_fn)(struct stream s);
typedef bool (*closed_fn)(struct stream);

// create a stream instance using the default functions
struct stream stream(void *data, size_t part_size, size_t length);

// create a stream instance using the provided custom functions and data pointer
struct stream customStream(peek_fn peek, advance_fn advance, closed_fn closed, void *data);

#endif