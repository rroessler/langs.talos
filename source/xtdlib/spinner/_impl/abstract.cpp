/// Library Includes
#include "xtdlib/spinner/abstract.hpp"
#include "xtdlib/mutex/lock.hpp"
#include "xtdlib/spinner/cursor.hpp"

//  CONSTRUCTORS  //

$::Spinner::Abstract::Abstract(const $::String::Buffer &text, Mode mode) : Abstract({.mode = mode, .suffix = text}) {}
$::Spinner::Abstract::Abstract(const Options &options) : m_options(options) {
  if (m_options.mode != Mode::RESOLVE) return; // check for auto-modes now
  m_options.mode = Enabled(m_options.output) ? Mode::ENABLED : Mode::PARTIAL;
}

//  PUBLIC METHODS  //

void $::Spinner::Abstract::refresh() {
  // we only force a refresh to occur for partial outputs
  if (m_options.mode == Mode::PARTIAL) m_print();
}

void $::Spinner::Abstract::refresh(const Color::ANSI &text) { suffix(text), refresh(); }
void $::Spinner::Abstract::refresh(const $::String::Buffer &text) { suffix(text), refresh(); }

void $::Spinner::Abstract::dismiss(const $::String::Buffer &text) {
  $_UNUSED $_AUTO = Lock::guard(m_mutex);
  if (m_complete) return; // finished here

  // latch the current completion details
  m_complete = true, m_dismiss();

  // handle the incoming modes now
  switch (m_options.mode) {
  // stop handling when in disabled mode
  default: return;

  // we allopw printing for enabled and partial modes
  case Mode::ENABLED: Cursor::toggle(m_options.output, true), m_clear(), (m_options.output << '\r'); $_FALLTHROUGH;
  case Mode::PARTIAL: m_options.output << text << (text.empty() ? "" : "\n"); break; // ensure we clear the queue
  }

  // flush the outgoing buffer now
  m_options.output.flush();
}

//  PRIVATE METHODS  //

void $::Spinner::Abstract::m_clear() { Cursor::clear(m_options.output), m_reset = true; }

void $::Spinner::Abstract::m_loop() {
  // handle the different modes as necessary
  switch (m_options.mode) {
  // ignore non-enabled modes here
  default: return;

  // for general enablement, we drop into below
  case Mode::ENABLED: break;

  // for partial enablement, we print once
  case Mode::PARTIAL: return m_print();
  }

  // ensure the cursor state is hidden
  Cursor::toggle(m_options.output, false);

  // handle dumping the spinner whilst running
  while (m_running()) m_print(), m_sleep();
}

void $::Spinner::Abstract::m_print() {
  // ignore if currently disabled
  if (m_options.mode == Mode::DISABLED) return;

  // ensure we lock whenever we write
  $_UNUSED $_AUTO = Lock::guard(m_mutex);

  // determine the padding to be used
  auto padding = m_options.prefix.empty() || m_options.prefix.ends_with(' ') ? "" : " ";

  // handle the incoming modes as necessary
  switch (m_options.mode) {
  // ignore printing when in disabled mode
  default: return;

  // handle showing regular spinners here
  case Mode::ENABLED: {
    // when a reset is called for, clear the line
    if (m_reset) m_clear();

    // show the leading prefix text now
    m_options.output << m_options.prefix << padding;

    // show the current frame value now
    if (const auto &frames = m_options.frames; frames.size()) m_options.output << frames[m_frame % frames.size()];

    // show the trailing suffix text now
    m_options.output << (m_options.suffix.starts_with(' ') ? "" : " ") << m_options.suffix << '\r';
  } break;

  // only show the immediate instance
  case Mode::PARTIAL: {
    m_options.output << m_options.prefix << padding;
    m_options.output << m_options.suffix << '\n';
  } break;
  }

  // always flush and increment the frame on completion
  m_options.output.flush(), m_frame += 1; // flush
}
