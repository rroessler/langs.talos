/// Package Modules
import { Task } from '../task';

/// Plugin Modules
import { Guards } from './guards';
import { Checkout } from './checkout';
import { Integrate } from './integrate';

/** Available Release Plugins. */
export const Plugins = (): Task.Factory[] => [Guards, Checkout, Integrate];
