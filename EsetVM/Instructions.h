#pragma once

namespace Core {
	namespace Utils {
		namespace Enums {
			enum Instructions {
				mov,
				loadConst,
				add,
				sub,
				div,
				mod,
				mul,
				compare,
				jump,
				jumpEqual,
				read,
				write,
				consoleRead,
				consoleWrite,
				createThread,
				joinThread,
				hlt,
				sleep,
				call,
				ret,
				lock,
				unlock
			};
		}
	}
}