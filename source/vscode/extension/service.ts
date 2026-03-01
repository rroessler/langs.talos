/// Talos Modules
import { Dependency, Disposable } from '@/talos/utilities';

/// Package Modules
import { Context } from './context';

/** Extension Service Interface. */
export const Service = Dependency.Name('extension.service');
export interface Service extends Disposable {
    context(): Context;
    activate(): Promise<void>;
}
