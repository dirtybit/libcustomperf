#ifndef __PERF_BUILTIN_RECORD_H
#define __PERF_BUILTIN_RECORD_H 1

#include "util/evlist.h"
#include "util/session.h"
#include "util/tool.h"

enum write_mode_t {
	WRITE_FORCE,
	WRITE_APPEND
};

struct perf_record {
	struct perf_tool	tool;
	struct perf_record_opts	opts;
	u64			bytes_written;
	const char		*output_name;
	struct perf_evlist	*evlist;
	struct perf_session	*session;
	const char		*progname;
	int			output;
	unsigned int		page_size;
	int			realtime_prio;
	enum write_mode_t	write_mode;
	bool			no_buildid;
	bool			no_buildid_cache;
	bool			force;
	bool			file_new;
	bool			append_file;
	long			samples;
	off_t			post_processing_offset;
};

#endif
